//
// Created by Gabriel Lugo on 3/27/2021.
//
#pragma once

namespace Flugel {
  class FLUGEL_API Stopwatch {
    using Clock = std::chrono::steady_clock;
    using Seconds = std::chrono::duration<double>;
  public:
    template<class Duration>
    using TimePoint = std::chrono::time_point<Clock, Duration>;

    Stopwatch() {
      FLUGEL_DEBUG_ENGINE("STOPWATCH (Created!)");
      reset();
    }

    void reset() {
      start_ = TimePoint<Seconds>{Seconds::zero()};
      // end_ = TimePoint<Seconds>{Seconds::zero()};
    }

    template<class Duration>
    void start(TimePoint<Duration> time_point) {
      reset();
      start_ = time_point;
    }
    void start() { start(Clock::now()); }

    // template<class Duration>
    // void stop(TimePoint<Duration> time_point) {
    //   end_ = time_point;
    // }
    // void stop() { stop(Clock::now()); }

    template<typename Duration>
    double getTimeElapsed() const {
      return TimePoint<Duration>{Clock::now() - start_}.time_since_epoch().count();
    }

    // Friends
    friend std::ostream&
    operator<<(std::ostream& output, const Stopwatch& interval) {
      interval.display(output);
      return output;
    }

  private:
    TimePoint<Seconds> start_{Seconds::zero()};
    // TimePoint<Seconds> end_{Seconds::zero()};
    // bool isStopped_;

    void display(std::ostream& output) const {
      output << getTimeElapsed<Seconds>();
    }
  };
}
