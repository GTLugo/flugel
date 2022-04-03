#pragma once

#include <utility>

#include "core/window/window.hpp"
#include "core/layers/layer_stack.hpp"

#include "core/threading/job_system.hpp"

#include "core/callbacks/event_system.hpp"
#include "core/callbacks/events/event.hpp"
#include "core/callbacks/events/app_event.hpp"
#include "core/callbacks/events/render_event.hpp"
#include "core/callbacks/events/logic_event.hpp"
#include "core/callbacks/notifier/notifier.hpp"

#include "core/ecs/world.hpp"

namespace ff {
  class App {
  public:
    explicit App(const WindowProperties& props = {});
    virtual ~App();

    static App& instance() { return *instance_; }
    Window& window() { return *window_; }

    void insertWorld(Unique<World> world) { worlds_.insert({world->name(), std::move(world)}); }
    World* activeWorld() { return activeWorld_; }
    void setActiveWorld(const std::string& name) { activeWorld_ = worlds_[name].get(); }
    //ECSManager& activeEntityManager() { return activeWorld_->entityManager(); } // helper function

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
    std::unordered_map<std::string, Unique<World>> worlds_{};
    World* activeWorld_{nullptr};

    void gameLoop(const std::stop_token& stopToken);

    void eventHandler(const Event& e);

    struct TimeJob : Job {
      float tickRate{};

      TimeJob(float tickRate) : tickRate{tickRate} {}

      void execute() override {
        Time::init(tickRate);
      }
    };

    struct EventSystemJob : Job {
      EventSystem::EventCallbackFn callbackFn;

      EventSystemJob(EventSystem::EventCallbackFn callbackFn) : callbackFn{std::move(callbackFn)} {}

      void execute() override {
        EventSystem::init(std::move(callbackFn));
      }
    };
  };

  Unique<App> createApp();
}