#include "app.hpp"

#include "core/layers/engine_layer.hpp"
#include "core/layers/world_layer.hpp"
#include "core/imgui/imgui_layer.hpp"
#include "core/ecs/components/transform.hpp"

// #include <boost/gil.hpp>
// #include <boost/gil/extension/io/png.hpp>
#include <boost/range/adaptor/reversed.hpp>


namespace ff {
  App::App(const WindowProperties& props) {
    Log::debug_e("Current working directory: {}", std::filesystem::current_path());
    Log::trace_e("Constructing App...");
    instance_ = this;
    JobSystem::init();

    // These are pointless, but just show how to use the job system
    TimeJob timeJob{128.f};
    EventSystemJob eventSystemJob{FF_LAMBDA(eventHandler)};
    JobSystem::kickJob({&timeJob, &eventSystemJob});
    timeJob.wait();
    eventSystemJob.wait();

    window_ = Window::create(props);
    window_->setEventCallback(FF_LAMBDA(eventHandler));

//    i32 width, height;
//    u8* icon{stbi_load("res/flugel/icon.png", &width, &height, nullptr, 4)};
//    window_->setIcon(icon, width, height);
//    stbi_image_free(icon);
    
    // engine layer should be first layer (last to check)
    pushLayer(new EngineLayer{});
    pushLayer(new WorldLayer{});
    layerStack_.pushBottomStack(new ImGuiLayer{});
  }

  App::~App() {
    Log::trace_e("Destructing App...");
    JobSystem::shutdown();
    EventSystem::shutdown();
  }

  void App::pushLayer(Layer* layer) {
    layerStack_.pushLayer(layer);
  }

  void App::pushOverlay(Layer* overlay) {
    layerStack_.pushOverlay(overlay);
  }

  void App::run() {
    Log::trace_e("Started main thread (ID: {})", std::this_thread::get_id());

    // GAME THREAD - App logic & rendering
    std::jthread gameThread{FF_LAMBDA(App::gameLoop)}; // jthread automatically joins on destruction
    // MAIN THREAD - OS message pump & main thread sensitive items
    EventSystem::handleEvent(AppEvent{AppEvent::Start});
    while (!shouldClose_) {
      EventSystem::handleEvent(AppEvent{AppEvent::Poll});
      EventSystem::handleEvent(AppEvent{AppEvent::Update});
    }
    EventSystem::handleEvent(AppEvent{AppEvent::Stop});
    gameThread.request_stop();

    Log::trace_e("Stopped main thread");
  }

  void App::close() {
    shouldClose_ = true;
  }

  void App::gameLoop(const std::stop_token& stopToken) {
    Log::trace_e("Started game thread (ID: {})", std::this_thread::get_id());
    window_->context().setCurrent(true);

    EventSystem::handleEvent(LogicEvent{LogicEvent::Start});
    EventSystem::handleEvent(RenderEvent{RenderEvent::Start});
    while (!stopToken.stop_requested()) {
      // Logic
      while (Time::shouldDoTick()) {
        // Physics & timestep sensitive stuff happens in here, where timestep is fixed
        // Source: https://gameprogrammingpatterns.com/game-loop.html#play-catch-up
        EventSystem::handleEvent(LogicEvent{LogicEvent::Tick});

        Time::tick();
      }
      EventSystem::handleEvent(LogicEvent{LogicEvent::Update});

      // Rendering
      EventSystem::handleEvent(RenderEvent{RenderEvent::BeginFrame});
      EventSystem::handleEvent(RenderEvent{RenderEvent::AppStep});
      EventSystem::handleEvent(RenderEvent{RenderEvent::ImGuiStep});
      EventSystem::handleEvent(RenderEvent{RenderEvent::EndFrame});

      Time::update();
    }
    EventSystem::handleEvent(LogicEvent{LogicEvent::Stop});
    EventSystem::handleEvent(RenderEvent{RenderEvent::Stop});

    Log::trace_e("Stopped game thread");
  }

  void App::eventHandler(const Event& e) {
    for (auto ritr{layerStack_.rbegin()}; ritr != layerStack_.rend(); ++ritr) {
      if (e.wasHandled()) break;
      (*ritr)->onEvent(e);
    }
  }
}