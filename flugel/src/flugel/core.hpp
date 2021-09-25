#pragma once

#ifdef FLUGEL_BUILD_DLL
  #ifdef _WIN32 // Windows
    #define FLUGEL_API __declspec(dllexport)
  #elif __GNUC__ >= 4 // GCC
    #define FLUGEL_API __attribute__((visibility("default")))
  #else // None
    #define FLUGEL_API
  #endif
#else
  #ifdef _WIN32
    #define FLUGEL_API __declspec(dllimport)
  #else // None
    #define FLUGEL_API
  #endif
#endif

#if defined(DEBUG) || defined(RELDEB)
  #ifdef _WIN32 // Windows
      #define DEBUG_BREAK __debugbreak()
  #else
    #include <csignal>
    #ifdef SIGTRAP // POSIX
      #define DEBUG_BREAK raise(SIGTRAP)
    #else // Other
      #define DEBUG_BREAK raise(SIGABRT)
    #endif
  #endif
#else
  #define DEBUG_BREAK
#endif

#ifdef FLUGEL_ENABLE_ASSERTS
  #define FLUGEL_ASSERT(x, ...) {\
    if(!(x)) {FLUGEL_ERROR("FAILED ASSERT: {0}", __VA_ARGS__); DEBUG_BREAK; }\
  }
  #define FLUGEL_ASSERT_E(x, ...) {\
    if(!(x)) {FLUGEL_ERROR_E("FAILED ASSERT: {0}", __VA_ARGS__); DEBUG_BREAK; }\
  }
#else
  #define FLUGEL_ASSERT(x, ...)
  #define FLUGEL_ASSERT_E(x, ...)
#endif

#define BIT(x) (1 << x)

#define FLUGEL_BIND_EVENT(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); } 

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
  template<typename Duration>
  using TimePoint = std::chrono::time_point<ClockSteady, Duration>;
  template<typename Duration>
  using TimePointAccurate = std::chrono::time_point<ClockAccurate, Duration>;
  template<typename Duration>
  using TimePointSystem = std::chrono::time_point<ClockSystem, Duration>;

  // Scope = std::unique_ptr
  template<typename T>
  using Unique = std::unique_ptr<T>;
  template<typename T, typename... Args>
  constexpr Unique<T> CreateUnique(Args&&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
  }

  // Ref = std::shared_ptr
  template<typename T>
  using Shared = std::shared_ptr<T>;
  template<typename T, typename... Args>
  constexpr Shared<T> CreateShared(Args&&... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
  }
}