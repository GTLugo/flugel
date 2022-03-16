#include "app.hpp"

#include "core/layers/render_layer.hpp"
#include "core/imgui/imgui_layer.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
// #include <boost/gil.hpp>
// #include <boost/gil/extension/io/png.hpp>
#include <boost/range/adaptor/reversed.hpp>

namespace ff {
  App::App(const WindowProperties& props) {
    Log::debug_e("Current working directory: {}", std::filesystem::current_path());
    Log::trace_e("Constructing App...");
    instance_ = this;
    Time::init(tickRate_);
    window_ = Window::create(props);
    window_->setEventCallback(FF_BIND_AS_LAMBDA(eventDispatch));
    Color::using_srgb_color_space = true;

    i32 width, height;
    // boost::gil::rgb8_image_t icon;
    // boost::gil::
    u8* icon{stbi_load("res/flugel/icon.png", &width, &height, nullptr, 4)};
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
    Log::trace_e("Destructing App...");
  }

  void App::pushLayer(Layer* layer) {
    layerStack_.pushLayer(layer);
  }

  void App::pushOverlay(Layer* overlay) {
    layerStack_.pushOverlay(overlay);
  }

  void App::run() {
    Log::trace_e("Started main thread (ID: {})", std::this_thread::get_id());
    AppEvent mainStartEvent{AppEvent::Start};
    eventDispatch(mainStartEvent);

    threadPool_.initialize();
    threadPool_.pushJob(FF_BIND_AS_LAMBDA(gameLoop));
    threadPool_.pushJob(FF_BIND_AS_LAMBDA(renderLoop));
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
    Log::trace_e("Stopped main thread");
  }

  void App::close() {
    shouldClose_ = true;
  }
  
  void App::renderLoop() {
    Log::trace_e("Started render thread (ID: {})", std::this_thread::get_id());
    window_->context().setCurrent(true);
    
    // RENDER THREAD
    RenderEvent renderStartEvent{RenderEvent::Start};
    eventDispatch(renderStartEvent);
    while (!shouldClose_) {
      waitForRenderJob();
    }
    RenderEvent renderEndEvent{RenderEvent::Stop};
    eventDispatch(renderEndEvent);

    Log::trace_e("Stopped render thread");
  }
  
  void App::gameLoop() {
    Log::trace_e("Started game thread (ID: {})", std::this_thread::get_id());

    // GAME LOGIC THREAD
    LogicEvent startEvent{LogicEvent::Start};
    eventDispatch(startEvent);
    while (!shouldClose_) {
      // This loop will only occur once every fixedTimeStep, being skipped for every
      // frame which happens between each timestep. If the deltaTime per frame is too
      // long, then for each frame, this loop will occur more than once in order to
      // "catch up" with the proper pacing of physics.
      // Source: https://gameprogrammingpatterns.com/game-loop.html#play-catch-up
      //Log::trace_e("UPDATE");
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

    Log::trace_e("Stopped game thread");
  }

  void App::waitForRenderJob() {
    RenderEvents* renderEvents{nullptr};

    {
      std::unique_lock<std::mutex> lock{renderMutex_};
      //Log::debug_e("Render thread waiting...");
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
      //Log::trace_e("Starting render job!");
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
//          Log::trace_e("{}: {}", (*itr)->name(), e);
//        }
        if (e.wasHandled()) {
          break;
        }
        (*itr)->onEvent(e);
      }
    } else {
      for (auto ritr = layerStack_.rbegin(); ritr != layerStack_.rend(); ++ritr) {
        //Log::trace_e("{}: {}", (*ritr)->name(), e);
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
    //Log::trace_e("{}: {}", engineLayer->name(), e);
  }
}