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
    window_ = Window::create(props);
    window_->setEventCallback(FGE_BIND(eventDispatch));
    Color::using_srgb_color_space = true;
    
    int32_t width, height;
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

    // MAIN THREAD
    while (!shouldClose_) {
      AppPollEvent pollEvent{};
      eventDispatch(pollEvent);

      AppUpdateEvent mainUpdateEvent{};
      eventDispatch(mainUpdateEvent);
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
      while (time_.shouldDoTick()) {
        // Physics & timestep sensitive stuff happens in here, where timestep is fixed
        LogicTickEvent tickEvent{};
        eventDispatch(tickEvent);

        time_.tick();
      }
      // Timestep INSENSITIVE stuff happens out here, where pacing goes as fast as possible
      LogicUpdateEvent updateEvent{};
      eventDispatch(updateEvent);

      RenderBeginFrameEvent beginFrameEvent{};
      RenderEndFrameEvent endFrameEvent{};
      pushRenderJob(beginFrameEvent, endFrameEvent);

      time_.update();
    }
    LogicStopEvent stopEvent{};
    eventDispatch(stopEvent);

    FGE_TRACE_ENG("Stopped game thread");
  }

  void App::waitForRenderJob() {
    RenderBeginFrameEvent beginFrameEvent;
    RenderEndFrameEvent endFrameEvent;

    {
      std::unique_lock<std::mutex> lock{renderMutex_};
      //FGE_DEBUG_ENG("Render thread waiting...");
      renderCondition_.wait(lock, [this]{
        return !renderBeginQueue_.empty() || shouldClose_; // only need to test one queue since it's 1-to-1
      });

      if (!shouldClose_) {
        beginFrameEvent = renderBeginQueue_.front();
        endFrameEvent = renderEndQueue_.front();
        renderBeginQueue_.pop();
        renderEndQueue_.pop();
      }
      //FGE_INFO_ENG("Render thread done waiting!");
    }

    if (!shouldClose_) {
      //FGE_TRACE_ENG("Starting render job!");
      eventDispatch(beginFrameEvent);
      eventDispatch(endFrameEvent);
    }
  }

  void App::pushRenderJob(RenderBeginFrameEvent& beginEvent, RenderEndFrameEvent& endEvent) {
    { // Mutex lock scope
      std::unique_lock<std::mutex> lock{renderMutex_};
      if (renderBeginQueue_.size() < 2) { // only need to test one queue since it's 1-to-1
        renderBeginQueue_.push(beginEvent);
        renderEndQueue_.push(endEvent);
      }
      // if (renderEndQueue_.size() < 2) {
      // }
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
    engineLayer->onEvent(e);
    //FGE_TRACE_ENG("{}: {}", engineLayer->name(), e);
  }
}