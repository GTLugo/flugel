#include "app.hpp"

#include "util/color/color.hpp"
#include "core/layers/render_layer.hpp"
#include "core/imgui/imgui_layer.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
// #include <boost/gil.hpp>
// #include <boost/gil/extension/io/png.hpp>
#include <boost/range/adaptor/reversed.hpp>

namespace fge {
  App::App(const WindowProperties& props) {
    FGE_DEBUG_ENG("Current working directory: {}", std::filesystem::current_path());
    FGE_TRACE_ENG("Constructing App...");
    instance_ = this;
    Time::init(tickRate_);
    window_ = Window::create(props);
    window_->setEventCallback(FGE_BIND(eventDispatch));
    Color::using_srgb_color_space = true;

    i32 width, height;
    // boost::gil::rgb8_image_t icon;
    // boost::gil::
    u8* icon = stbi_load("res/flugel/icon.png", &width, &height, nullptr, 4);
    window_->setIcon(icon, width, height);
    stbi_image_free(icon);
    
    // engine layer should be first layer (last to check)
    pushLayer(new EngineLayer{});
    layerStack_.pushBottomStack(new ImGuiLayer{});
    layerStack_.pushBottomStack(new RenderLayer{});

    //#if defined(DEBUG) || defined(RELDEB)
    //#endif
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

  void App::toggleImGui(bool enabled) {
    (*(layerStack_.end() - 2))->toggle(enabled);
  }

  void App::run() {
    FGE_TRACE_ENG("Started main thread (ID: {})", std::this_thread::get_id());
    AppEvent mainStartEvent{AppEvent::Start};
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
      AppEvent pollEvent{AppEvent::Poll};
      eventDispatch(pollEvent);

      AppEvent mainUpdateEvent{AppEvent::Update};
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
    
    AppEvent mainEndEvent{AppEvent::Stop};
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
    RenderEvent renderStartEvent{RenderEvent::Start};
    eventDispatch(renderStartEvent);
    while (!shouldClose_) {
      waitForRenderJob();
    }
    RenderEvent renderEndEvent{RenderEvent::Stop};
    eventDispatch(renderEndEvent);

    FGE_TRACE_ENG("Stopped render thread");
  }
  
  void App::gameLoop() {
    FGE_TRACE_ENG("Started game thread (ID: {})", std::this_thread::get_id());

    // GAME LOGIC THREAD
    LogicEvent startEvent{LogicEvent::Start};
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
        LogicEvent tickEvent{LogicEvent::Tick};
        eventDispatch(tickEvent);

        Time::tick();
      }
      // Timestep INSENSITIVE stuff happens out here, where pacing goes as fast as possible
      LogicEvent updateEvent{LogicEvent::Update};
      eventDispatch(updateEvent);

      pushRenderJob(new RenderEvents{
        RenderEvent{RenderEvent::BeginFrame},
        RenderEvent{RenderEvent::AppStep},
        RenderEvent{RenderEvent::ImGuiStep},
        RenderEvent{RenderEvent::EndFrame}
      });

      Time::update();
    }
    LogicEvent stopEvent{LogicEvent::Stop};
    eventDispatch(stopEvent);

    FGE_TRACE_ENG("Stopped game thread");
  }

  void App::waitForRenderJob() {
    RenderEvents* renderEvents{nullptr};

    {
      std::unique_lock<std::mutex> lock{renderMutex_};
      //FGE_DEBUG_ENG("Render thread waiting...");
      renderCondition_.wait(lock, [this]{
        return renderQueue_.size() >= maxFramesInFlight_ || shouldClose_;
      });

      if (renderQueue_.size() >= maxFramesInFlight_) {
        renderEvents = renderQueue_.front();
        renderQueue_.pop();
      }
      //FGE_INFO_ENG("Render thread done waiting!");
    }

    if (renderEvents) {
      //FGE_TRACE_ENG("Starting render job!");
      for (auto& renderEvent : *renderEvents) {
        eventDispatch(renderEvent);
      }
      delete renderEvents;
    }
  }

  void App::pushRenderJob(RenderEvents* renderEvents) {
    { // Mutex lock scope
      std::unique_lock<std::mutex> lock{renderMutex_};
      if (renderQueue_.size() < maxFramesInFlight_) {
        renderQueue_.push(renderEvents);
      }
    } // Unlock mutex

    renderCondition_.notify_all();
  }
  
  void App::eventDispatch(Event& e) {
    //bool inputEvent = (e.category() | Event::Category::Input);
    if (e.type() == Event::Render) {
      for (auto itr = layerStack_.begin(); itr != layerStack_.end(); ++itr) {
//        if ((*itr)->name() == "imgui_layer") {
//          FGE_TRACE_ENG("{}: {}", (*itr)->name(), e);
//        }
        if (e.wasHandled()) {
          break;
        }
        (*itr)->onEvent(e);
      }
    } else {
      for (auto ritr = layerStack_.rbegin(); ritr != layerStack_.rend(); ++ritr) {
        //FGE_TRACE_ENG("{}: {}", (*ritr)->name(), e);
        if (e.wasHandled()) {
          break;
        }
        (*ritr)->onEvent(e);
      }
    }

//    auto& engineLayer = *layerStack_.begin();
//    if (!(inputEvent && e.wasHandled())) {
//      engineLayer->onEvent(e);
//    }
    //FGE_TRACE_ENG("{}: {}", engineLayer->name(), e);
  }
}