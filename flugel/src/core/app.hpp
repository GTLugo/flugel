#pragma once

#include "core/events/event.hpp"
#include "core/events/app_event.hpp"
#include "core/events/window_event.hpp"
#include "core/events/mouse_event.hpp"
#include "core/window/window.hpp"

namespace Flugel {
  class FLUGEL_API App {
  public:
    App(const WindowProperties& props = {});
    virtual ~App();

    Time getTime() const { return time_; }

    void run();
  private:
    Time time_{};
    // Window
    bool shouldClose_{false};
    Window window_;
    // Threads
    std::thread gameThread_;
    std::thread renderThread_;
    // App Data
    bool leftMouseHeld{false};

  private:
    void spawnThreads();
    void killThreads();

    void gameThreadMain();
    void renderThreadMain();

    void processInput();
    void updateFixed();
    void update();
    void render();
    
    void onEvent(Event& e);
  };

  // To be defined in project app
  Unique<App> createApp();
}