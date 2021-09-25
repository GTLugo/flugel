#pragma once

#include "window.hpp"
#include "time/time.hpp"
#include "events/window_event.hpp"
#include "events/app_event.hpp"

namespace Flugel {
  class FLUGEL_API App {
  public:
    App(const WindowProps& props = {});
    virtual ~App();

    Time getTime() const { return time_; }

    void run();
    void onEvent(Event& e);
  private:
    Unique<Window> window_;
    bool shouldClose_{false};

    Time time_{};
  protected:
    // Overrideable Lifetime events
    virtual bool onStart(AppStartEvent& e);
    virtual bool onTick(AppTickEvent& e);
    virtual bool onUpdate(AppUpdateEvent& e);
    virtual bool onRender(AppRenderEvent& e);
    // Events
    bool onWindowClosed(WindowCloseEvent& e);
  };

  // To be defined in project app
  App* CreateApp();
}