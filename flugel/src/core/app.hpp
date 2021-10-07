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

  private:
    void spawnThreads();
    void killThreads();

    void gameThreadMain();
    void renderThreadMain();

    std::map<std::thread::id, std::string> threadNames_{};

    void processInput();

    void updateFixed();
    void update();
    void render();
    void close();
    
    void eventDispatch(Event& e);
    bool onAppEvent(AppEvent& e);
    bool onWindowEvent(WindowEvent& e);
    bool onKeyboardEvent(KeyboardEvent& e);
    bool onMouseEvent(MouseEvent& e);
    bool onCursorEvent(CursorEvent& e);
    bool onScrollEvent(ScrollEvent& e);
  };

  // To be defined in project app
  Unique<App> createApp();
}