#pragma once

#include "window.hpp"
#include "time/time.hpp"

namespace Flugel {
  class FLUGEL_API App {
  public:
    App(const WindowProps& props = {}, bool shouldUseFlugelTagInTitle = true);
    virtual ~App();

    Time getTime() const { return time_; }

    void run();

    void onStart();
    void onTick();
    void onUpdate();
    void onRender();
  private:
    Unique<Window> window_;
    bool shouldClose_{false};

    Time time_{};
    // Stopwatch fps_stopwatch_{};
  };

  // To be defined in project app
  App* CreateApp();
}