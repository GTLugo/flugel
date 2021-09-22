//
// Created by Gabriel Lugo on 3/27/2021.
//
#pragma once

namespace Flugel {
  class FLUGEL_API Stopwatch {
  public:
    Stopwatch() {
      FLUGEL_DEBUG_ENGINE("STOPWATCH (Created!)");
      reset();
    }

    void reset() {
      start_ = TimePoint<Seconds>{Seconds::zero()};
    }

    template<class Duration>
    void start(TimePoint<Duration> time_point) {
      reset();
      start_ = time_point;
    }
    void start() { start(ClockSteady::now()); }

    template<typename Duration>
    double getTimeElapsed() const {
      return std::chrono::duration_cast<Duration>(ClockSteady::now() - start_).count();
    }

    // Friends
    friend std::ostream&
    operator<<(std::ostream& output, const Stopwatch& interval) {
      interval.display(output);
      return output;
    }

  private:
    TimePoint<Seconds> start_{Seconds::zero()};

    void display(std::ostream& output) const {
      output << getTimeElapsed<Seconds>();
    }
  };
}
