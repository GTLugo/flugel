#include "app.hpp"

#include "core/input/input.hpp"

#include "util/color/color.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
// #include <boost/gil.hpp>
// #include <boost/gil/extension/io/png.hpp>
#include <boost/range/adaptor/reversed.hpp>

namespace fge {
  App* App::instance_ = nullptr;

  App::App(const WindowProperties& props) {
    FGE_DEBUG_ENG("Current working directory: {}", std::filesystem::current_path());
    FGE_TRACE_ENG("Constructing App...");
    instance_ = this;
    Time::init(128.);
    window_ = Window::create(props);
    window_->setEventCallback(FGE_BIND(eventDispatch));
    Color::using_srgb_color_space = true;

    i32 width, height;
    // boost::gil::rgb8_image_t icon;
    // boost::gil::
    uint8_t* icon = stbi_load("res/flugel/icon.png", &width, &height, 0, 4);
    window_->setIcon(icon, width, height);
    stbi_image_free(icon);
    
    // engine layer should be first layer (last to check)
    pushLayer(new EngineLayer{});
  }

  App::~App() {
    FGE_TRACE_ENG("Destructing App...");
  }

  void App::pushLayer(Layer* layer) {
    layerStack_.pushLayer(layer);
  }

  void App::pushOverlay(Layer* overlay) {
    layerStack_.pushOverlay(overlay);
  }

  void App::run() {
    FGE_TRACE_ENG("Started main thread (ID: {})", std::this_thread::get_id());
    AppStartEvent mainStartEvent{};
    eventDispatch(mainStartEvent);

    threadPool_.initialize();
    threadPool_.pushJob(FGE_BIND(gameLoop));
    threadPool_.pushJob(FGE_BIND(renderLoop));
    //window_->context().setCurrent(true);
    //
    //// RENDER THREAD
    //RenderStartEvent renderStartEvent{};
    //eventDispatch(renderStartEvent);
    // MAIN THREAD
    while (!shouldClose_) {
      AppPollEvent pollEvent{};
      eventDispatch(pollEvent);

      AppUpdateEvent mainUpdateEvent{};
      eventDispatch(mainUpdateEvent);
      //RenderBeginFrameEvent beginFrameEvent{};
      //eventDispatch(beginFrameEvent);
      //RenderBeginImGuiEvent beginImGuiEvent{};
      //eventDispatch(beginImGuiEvent);
      //RenderEndImGuiEvent endImGuiEvent{};
      //eventDispatch(endImGuiEvent);
      //RenderEndFrameEvent endFrameEvent{};
      //eventDispatch(endFrameEvent);
    }

    renderCondition_.notify_all();
    threadPool_.shutdown();
    
    AppStopEvent mainEndEvent{};
    eventDispatch(mainEndEvent);
    FGE_TRACE_ENG("Stopped main thread");
  }

  void App::close() {
    shouldClose_ = true;
  }
  
  void App::renderLoop() {
    FGE_TRACE_ENG("Started render thread (ID: {})", std::this_thread::get_id());
    window_->context().setCurrent(true);
    
    // RENDER THREAD
    RenderStartEvent renderStartEvent{};
    eventDispatch(renderStartEvent);
    while (!shouldClose_) {
      waitForRenderJob();
    }
    RenderStopEvent renderEndEvent{};
    eventDispatch(renderEndEvent);

    FGE_TRACE_ENG("Stopped render thread");
  }
  
  void App::gameLoop() {
    FGE_TRACE_ENG("Started game thread (ID: {})", std::this_thread::get_id());

    // GAME LOGIC THREAD
    LogicStartEvent startEvent{};
    eventDispatch(startEvent);
    while (!shouldClose_) {
      // This loop will only occur once every fixedTimeStep, being skipped for every
      // frame which happens between each timestep. If the deltaTime per frame is too
      // long, then for each frame, this loop will occur more than once in order to
      // "catch up" with the proper pacing of physics.
      // Source: https://gameprogrammingpatterns.com/game-loop.html#play-catch-up
      //FGE_TRACE_ENG("UPDATE");
      while (Time::shouldDoTick()) {
        // Physics & timestep sensitive stuff happens in here, where timestep is fixed
        LogicTickEvent tickEvent{};
        eventDispatch(tickEvent);

        Time::tick();
      }
      // Timestep INSENSITIVE stuff happens out here, where pacing goes as fast as possible
      LogicUpdateEvent updateEvent{};
      eventDispatch(updateEvent);
      
      pushRenderJob(new RenderBeginFrameEvent{});
      pushRenderJob(new RenderBeginImGuiEvent{});
      pushRenderJob(new RenderEndImGuiEvent{});
      pushRenderJob(new RenderEndFrameEvent{});

      Time::update();
    }
    LogicStopEvent stopEvent{};
    eventDispatch(stopEvent);

    FGE_TRACE_ENG("Stopped game thread");
  }

  void App::waitForRenderJob() {
    RenderBeginFrameEvent* beginFrameEvent{nullptr};
    RenderBeginImGuiEvent* beginImGuiEvent{nullptr};
    RenderEndImGuiEvent*   endImGuiEvent{nullptr};
    RenderEndFrameEvent*   endFrameEvent{nullptr};

    {
      std::unique_lock<std::mutex> lock{renderMutex_};
      //FGE_DEBUG_ENG("Render thread waiting...");
      renderCondition_.wait(lock, [this]{
        return renderQueue_.size() >= 4 || shouldClose_;
      });

      if (renderQueue_.size() >= 4) {
        beginFrameEvent = dynamic_cast<RenderBeginFrameEvent*>(renderQueue_.front());
        renderQueue_.pop();
        beginImGuiEvent = dynamic_cast<RenderBeginImGuiEvent*>(renderQueue_.front());
        renderQueue_.pop();
        endImGuiEvent = dynamic_cast<RenderEndImGuiEvent*>(renderQueue_.front());
        renderQueue_.pop();
        endFrameEvent = dynamic_cast<RenderEndFrameEvent*>(renderQueue_.front());
        renderQueue_.pop();
      }
      //FGE_INFO_ENG("Render thread done waiting!");
    }

    if (beginFrameEvent && beginImGuiEvent && endImGuiEvent && endFrameEvent) {
      //FGE_TRACE_ENG("Starting render job!");
      eventDispatch(*beginFrameEvent);
      delete beginFrameEvent;
      eventDispatch(*beginImGuiEvent);
      delete beginImGuiEvent;
      eventDispatch(*endImGuiEvent);
      delete endImGuiEvent;
      eventDispatch(*endFrameEvent);
      delete endFrameEvent;
    }
  }

  void App::pushRenderJob(RenderEvent* renderEvent) {
    { // Mutex lock scope
      std::unique_lock<std::mutex> lock{renderMutex_};
      const u32 MaxFrames = 2;
      if (renderQueue_.size() < MaxFrames * 4) {
        renderQueue_.push(renderEvent);
      }
    } // Unlock mutex

    renderCondition_.notify_all();
  }
  
  void App::eventDispatch(Event& e) {
    if (e.category() == EventCategory::Render) {
      for (auto itr = layerStack_.begin() + 1; itr != layerStack_.end(); ++itr) {
        //FGE_TRACE_ENG("{}: {}", (*itr)->name(), e);
        if (e.wasHandled()) {
          break;
        }
        (*itr)->onEvent(e);
		  }
    } else {
      for (auto ritr = layerStack_.rbegin(); ritr != layerStack_.rend() - 1; ++ritr) {
        //FGE_TRACE_ENG("{}: {}", (*itr)->name(), e);
        if (e.wasHandled()) {
          break;
        }
        (*ritr)->onEvent(e);
		  }
    }

    auto& engineLayer = *layerStack_.begin();
    bool inputEvent = (e.category() == EventCategory::Keyboard ||
                       e.category() == EventCategory::Cursor ||
                       e.category() == EventCategory::Mouse ||
                       e.category() == EventCategory::Scroll);
    if (!(inputEvent && e.wasHandled())) {
      engineLayer->onEvent(e);
    }
    //FGE_TRACE_ENG("{}: {}", engineLayer->name(), e);
  }
}