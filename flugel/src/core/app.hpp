#pragma once

#include "core/events/notifier.hpp"
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
    bool shouldClose_{false};
    Time time_{};
    Window window_;

    // App Events
    Notifier<AppUpdateFixedEvent> updateFixedNotifier_{};
    Notifier<AppUpdateEvent> updateNotifier_{};
    Notifier<AppRenderEvent> renderNotifier_{};
    
    UUID appUpdateId_{};
    UUID appUpdateFixedId_{};
    UUID appRenderId_{};
    // Window Events
    UUID windowCloseId_{};
    UUID windowResizeId_{};
    UUID windowMovedId_{};
    // Mouse Events
    UUID mousePressedId_{};
    UUID mouseReleasedId_{};
    UUID mouseMovedId_{};
    UUID mouseScrolledId_{};
    // Key Events
    UUID keyPressedId_{};
    UUID keyReleasedId_{};
  private:
    void processInput();
    // App Events
    bool onAppUpdateFixed(AppUpdateFixedEvent& e);
    bool onAppUpdate(AppUpdateEvent& e);
    bool onAppRender(AppRenderEvent& e);
    // Window Events
    bool onWindowClose(WindowCloseEvent& e);
    bool onWindowResize(WindowResizeEvent& e);
    bool onWindowMoved(WindowMovedEvent& e);
    // Mouse Events
    bool onMousePressed(MousePressedEvent& e);
    bool onMouseReleased(MouseReleasedEvent& e);
    bool onMouseMoved(MouseMovedEvent& e);
    bool onMouseScrolled(MouseScrolledEvent& e);
    // Key Events
    bool onKeyPressed(KeyPressedEvent& e);
    bool onKeyReleased(KeyReleasedEvent& e);
  };

  // To be defined in project app
  Unique<App> createApp();
}