//
// Created by Gabriel Lugo on 3/29/2021.
//
#pragma once

#include "stopwatch.hpp"

namespace Flugel {
  // duration types
  using NanoSeconds = std::chrono::duration<double, std::nano>;
  using MicroSeconds = std::chrono::duration<double, std::micro>;
  using MilliSeconds = std::chrono::duration<double, std::milli>;
  using Seconds = std::chrono::duration<double>;
  using Minutes = std::chrono::duration<double, std::ratio<60>>;
  using Hours = std::chrono::duration<double, std::ratio<3600>>;
  // clock types
  using ClockSystem = std::chrono::system_clock;
  using ClockSteady = std::chrono::steady_clock;
  using ClockAccurate = std::chrono::high_resolution_clock;

  template<typename Duration>
  using TimePoint = std::chrono::time_point<ClockSteady, Duration>;
  
  class FLUGEL_API Time {
  public:
    void initialize();
    void tick();

    template<class Duration>
    double deltaTime() const {
      return std::chrono::time_point_cast<Duration>(delta_).time_since_epoch().count();
    }

  private:
    TimePoint<Seconds> gameLast_{Seconds::zero()};
    TimePoint<Seconds> gameCurrent_{Seconds::zero()};
    TimePoint<Seconds> delta_{Seconds::zero()};
  };
}