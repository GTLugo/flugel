#pragma once

namespace Flugel {
  class FLUGEL_API App {
    using Clock = std::chrono::steady_clock;
    using Second = std::chrono::duration<double>;
    using TimePoint = std::chrono::time_point<Clock>;
  public:
    App();
    virtual ~App();

    void run();
  private:
  };

  // To be defined in project app
  App* CreateApp();
}