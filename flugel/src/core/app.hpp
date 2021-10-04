#pragma once

#include "core/events/notifier.hpp"
#include "core/events/app_event.hpp"
#include "core/events/window_event.hpp"
#include "core/window/window.hpp"

namespace Flugel {
  class FLUGEL_API App {
  public:
    App();
    virtual ~App();

    Time getTime() const { return time_; }

    void run();
  private:
    bool shouldClose_{false};
    Time time_{};
    Window window_{};

    // App Events
    Notifier<AppUpdateEvent> updateNotifier{};
    UUID appUpdateId_{};
    Notifier<AppUpdateFixedEvent> updateFixedNotifier{};
    UUID appUpdateFixedId_{};
    Notifier<AppRenderEvent> renderNotifier{};
    UUID appRenderId_{};
    Notifier<AppTickEvent> tickNotifier{}; // unused dummy
    UUID appTickId_{};

    // Window Events
    UUID windowCloseId_{};
  private:
    void processInput();
    bool onAppUpdateFixed(AppUpdateFixedEvent& e);
    bool onAppUpdate(AppUpdateEvent& e);
    bool onAppRender(AppRenderEvent& e);
    bool onAppTick(AppTickEvent& e);
    bool onWindowClose(WindowCloseEvent& e);
  };

  // To be defined in project app
  Unique<App> createApp();
}