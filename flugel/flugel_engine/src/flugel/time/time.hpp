//
// Created by Gabriel Lugo on 3/29/2021.
//
#pragma once

#include "stopwatch.hpp"

namespace Flugel {
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