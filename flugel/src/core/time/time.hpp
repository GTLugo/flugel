//
// Created by Gabriel Lugo on 3/27/2021.
//
#pragma once

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
  // time point
  using TimePoint = ClockSteady::time_point;
  using TimePointAccurate = ClockAccurate::time_point;
  using TimePointSystem = ClockSystem::time_point;

  class FLUGEL_API Stopwatch {
  public:
    Stopwatch() {
      start();
    }

    Stopwatch(TimePoint timePoint) {
      start(timePoint);
    }

    void start(TimePoint timePoint) {
      start_ = timePoint;
    }

    void start() { start(ClockSteady::now()); }

    template<typename Duration>
    double startTime() const {
      return std::chrono::time_point_cast<Duration>(start_).time_since_epoch().count();
    }

    template<typename Duration>
    double getTimeElapsed() const {
      return std::chrono::duration_cast<Duration>(ClockSteady::now() - start_).count();
    }
  private:
    TimePoint start_{};
  };

  class FLUGEL_API Time {
  public:
    Time()
      : stopwatch_{ClockSteady::now()}, gameLast_{ClockSteady::now()}, gameCurrent_{ClockSteady::now()} {
      FLUGEL_INFO_E("Initialized time!");
    }
    ~Time() = default;

    void tick() {
      // FLUGEL_ENGINE_TRACE("Tick!");
      gameCurrent_ = ClockSteady::now();
      delta_ = std::chrono::duration_cast<Seconds>(gameCurrent_ - gameLast_);
      gameLast_ = gameCurrent_;
      lag_ += delta_;
      stepCount_ = 0U;
    }

    void tickLag() {
      // FLUGEL_ENGINE_TRACE("Tock!");
      lag_ -= fixedTimeStep_;
      ++stepCount_;
    }

    template<class Duration>
    double startTime() const {
      return stopwatch_.startTime<Duration>();
    }

    template<class Duration>
    double timeSinceStart() const {
      return stopwatch_.getTimeElapsed<Duration>();
    }

    template<class Duration>
    double deltaTime() const {
      return std::chrono::duration_cast<Duration>(delta_).count();
    }

    template<class Duration>
    double lagTime() const {
      return std::chrono::duration_cast<Duration>(lag_).count();
    }

    template<class Duration>
    double fixedTimeStep() const {
      return std::chrono::duration_cast<Duration>(fixedTimeStep_).count();
    }

    bool shouldDoFixedStep() const {
      #if defined(DEBUG) || defined(RELDEB)
        if (stepCount_ >= bailCount_) {
          FLUGEL_WARN("Struggling to catch up with physics rate!");
        }
      #endif
      
      return lag_.count() >= fixedTimeStep_.count() && stepCount_ < bailCount_;
    }
  private:
    // fixed update pace. this will be used for physics and anything else in fixed update
    static constexpr double fixedTickRate_{128.};
    static constexpr Seconds fixedTimeStep_{1. / fixedTickRate_};
    // bail out of the fixed updates if iterations exceeds this amount to prevent lockups
    // on extremely slow systems where updateFixed may be longer than fixedTimeStep_
    static constexpr uint32_t bailCount_{128U};

    const Stopwatch stopwatch_;
    TimePoint gameLast_{}; // when last frame started
    TimePoint gameCurrent_{}; // when this frame started
    Seconds delta_{Seconds::zero()}; // how much time last frame took
    Seconds lag_{Seconds::zero()}; // how far behind the game is from real world
    uint32_t stepCount_{0U};
  };
}