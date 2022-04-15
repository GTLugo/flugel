#include "app.hpp"

#include "core/layers/engine_layer.hpp"
#include "core/layers/world_layer.hpp"
#include "core/imgui/imgui_layer.hpp"

// #include <boost/gil.hpp>
// #include <boost/gil/extension/io/png.hpp>
#include <boost/range/adaptor/reversed.hpp>

namespace ff {
  App::App(const WindowProperties& props) {
    Log::debug_e("Current working directory: {}", std::filesystem::current_path());
    Log::trace_e("Constructing App...");
    instance_ = this;
    JobManager::init();

    // These are pointless, but just show how to use the job system
    std::vector<Shared<Job>> jobs{makeShared<TimeJob>(128.f), makeShared<EventSystemJob>(FF_LAMBDA(eventHandler))};
    JobManager::submit(jobs);
    for (auto&& job: jobs) {
      job->wait();
    }

    window_ = Window::create(props);
    
    // engine layer should be first layer (last to check)
    pushLayer(new EngineLayer{});
    pushLayer(new WorldLayer{});
    layerStack_.pushBottomStack(new ImGuiLayer{});
  }

  App::~App() {
    Log::trace_e("Destructing App...");
    JobManager::shutdown();
    EventManager::shutdown();
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
    auto gameThreadJob{makeShared<GameJob>(*this)};
    JobManager::submit(gameThreadJob);
    // MAIN THREAD - OS message pump & main thread sensitive items
    EventManager::submit(MainAwakeEvent{});
    EventManager::submit(MainStartEvent{});
    while (!shouldClose_) {
      EventManager::submit(MainPollEvent{});
      EventManager::submit(MainUpdateEvent{});
    }
    gameThreadJob->wait();
    EventManager::submit(MainStopEvent{});

    Log::trace_e("Stopped main thread");
  }

  void App::close() {
    shouldClose_ = true;
  }

  void App::gameLoop() {
    Log::trace_e("Started game thread (ID: {})", std::this_thread::get_id());

    try {
      window_->context().setCurrent(true);

      EventManager::submit(GameAwakeEvent{});
      EventManager::submit(GameStartEvent{});
      while (!shouldClose_) {
        // Logic
        while (Time::shouldDoTick()) {
          // Physics & timestep sensitive stuff happens in here, where timestep is fixed
          // Source: https://gameprogrammingpatterns.com/game-loop.html#play-catch-up
          EventManager::submit(GameTickEvent{});

          Time::tick();
        }
        EventManager::submit(GameUpdateEvent{});

        // Rendering pipeline
        EventManager::submit(GameBeginFrameEvent{});
        EventManager::submit(GameDrawEvent{});
        EventManager::submit(GameImGuiEvent{});
        EventManager::submit(GameEndFrameEvent{});

        Time::update();
      }
      EventManager::submit(GameStopEvent{});
    } catch (const std::exception& e) {
      ff::Log::critical_e(e.what());
    }

    Log::trace_e("Stopped game thread");
  }

  void App::eventHandler(const Event& e) {
    for (auto& layer: layerStack_ | std::views::reverse) {
      if(layer->onEvent(e)) break;
    }
  }
}

// if you are reading this, just know that Shirakami Fubuki is the best fox waifu friend