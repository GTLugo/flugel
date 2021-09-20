
/*----------------------
  STD LIBRARY
----------------------*/

// IO
#include <iostream>
#include <iomanip>
#include <sstream>
// Utilities
#include <cstdlib>
#include <algorithm>
#include <utility>
#include <functional>
#include <memory>
#include <thread>
#include <ctime>
#include <chrono>
#include <stdexcept>
// Data Structures
#include <string>
#include <array>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <deque>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

#if defined(_WIN32) && defined(NDEBUG)
#include <windows.h>
#endif

/*----------------------
  FLUGEL LIBRARY
----------------------*/

#include "flugel/core.hpp"
#include "flugel/logging/log.hpp"

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
}