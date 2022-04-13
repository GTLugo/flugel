#pragma once

#include <utility>

#include "core/window/window.hpp"
#include "core/layers/layer_stack.hpp"

#include "core/threading/job_system.hpp"
#include "core/callbacks/event_system.hpp"
#include "core/callbacks/notifier/notifier.hpp"

#include "core/ecs/world.hpp"

namespace ff {
  class App {
  public:
    explicit App(const WindowProperties& props = {});
    virtual ~App();

    static App& instance() { return *instance_; }

    Window& window() { return *window_; }

    World* activeWorld() { return activeWorld_; }
    void setActiveWorld(const std::string& name) { activeWorld_ = worlds_[name].get(); }
    void setActiveWorld(const Shared<World>& world) { activeWorld_ = worlds_[world->name()].get(); }

    void insertWorld(const Shared<World>& world) { worlds_.insert({world->name(), world}); }
    void insertWorldAsActive(const Shared<World>& world) {
      insertWorld(world);
      setActiveWorld(world);
    }

    void pushLayer(Layer* layer);
    void pushOverlay(Layer* overlay);

    void run();
    void close();

    App(const App& app) = delete;
    App& operator=(const App& app) = delete;
  private:
    static inline App* instance_{nullptr};

    // Window
    Unique<Window> window_;
    bool shouldClose_{false};

    // Layers
    LayerStack layerStack_;

    // Misc
    std::unordered_map<std::string, Shared<World>> worlds_{};
    World* activeWorld_{nullptr};

    void gameLoop();

    void eventHandler(const Event& e);

    struct GameJob : Job {
      App& app;

      GameJob(App& app) : app{app} {}

      void execute() override {
        Log::trace_e("GameJob thread: {}", std::this_thread::get_id());
        app.gameLoop();
      }
    };

    struct TimeJob : Job {
      float tickRate{};

      TimeJob(float tickRate) : tickRate{tickRate} {}

      void execute() override {
        Log::trace_e("TimeJob thread: {}", std::this_thread::get_id());
        Time::init(tickRate);
      }
    };

    struct EventSystemJob : Job {
      EventManager::EventCallback callbackFn;

      EventSystemJob(EventManager::EventCallback callbackFn) : callbackFn{std::move(callbackFn)} {}

      void execute() override {
        Log::trace_e("EventSystemJob thread: {}", std::this_thread::get_id());
        EventManager::init(std::move(callbackFn));
      }
    };
  };

  Unique<App> createApp();
}