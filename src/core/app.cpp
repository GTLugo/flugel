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
    auto timeJob{makeShared<TimeJob>(128.f)};
    auto eventSystemJob{makeShared<EventSystemJob>(FF_LAMBDA(eventHandler))};
    JobSystem::submit({timeJob, eventSystemJob});
    timeJob->wait();
    eventSystemJob->wait();

    window_ = Window::create(props);
    
    // engine layer should be first layer (last to check)
    pushLayer(new EngineLayer{});
    pushLayer(new WorldLayer{});
    layerStack_.pushBottomStack(new ImGuiLayer{});
  }

  App::~App() {
    Log::trace_e("Destructing App...");
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
    auto gameJob{makeShared<GameJob>(*this)};
    JobSystem::submit(gameJob);
    //std::jthread gameThread{FF_LAMBDA(App::gameLoop)}; // jthread automatically joins on destruction

    // MAIN THREAD - OS message pump & main thread sensitive items
    EventSystem::handleEvent(MainAwakeEvent{});
    EventSystem::handleEvent(MainStartEvent{});
    while (!shouldClose_) {
      EventSystem::handleEvent(MainPollEvent{});
      EventSystem::handleEvent(MainUpdateEvent{});
    }
    gameJob->wait();
    //gameThread.request_stop();
    EventSystem::handleEvent(MainStopEvent{});

    JobSystem::shutdown();
    Log::trace_e("Stopped main thread");
  }

  void App::close() {
    shouldClose_ = true;
  }

  void App::gameLoop() {
    Log::trace_e("Started game thread (ID: {})", std::this_thread::get_id());

    try {
      window_->context().setCurrent(true);

      EventSystem::handleEvent(GameAwakeEvent{});
      EventSystem::handleEvent(GameStartEvent{});
      while (!shouldClose_) {
        // Logic
        while (Time::shouldDoTick()) {
          // Physics & timestep sensitive stuff happens in here, where timestep is fixed
          // Source: https://gameprogrammingpatterns.com/game-loop.html#play-catch-up
          EventSystem::handleEvent(GameTickEvent{});

          Time::tick();
        }
        EventSystem::handleEvent(GameUpdateEvent{});

        // Rendering pipeline
        EventSystem::handleEvent(GameBeginFrameEvent{});
        EventSystem::handleEvent(GameDrawEvent{});
        EventSystem::handleEvent(GameImGuiEvent{});
        EventSystem::handleEvent(GameEndFrameEvent{});

        Time::update();
      }
      EventSystem::handleEvent(GameStopEvent{});
    } catch (const std::exception& e) {
      ff::Log::critical_e(e.what());
    }

    Log::trace_e("Stopped game thread");
  }

  void App::eventHandler(const Event& e) {
    for (auto& layer: layerStack_ | std::views::reverse) {
      // TODO: Fix event handling
      bool handled{layer->onEvent(e)};
      // e.handled_ = handled;
    }
  }
}

// if you are reading this, just know that Shirakami Fubuki is the best fox waifu friend