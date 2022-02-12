#pragma once
/*----------------------
  STD LIBRARY
----------------------*/

// IO
#include <iostream>
#include <iomanip>
#include <sstream>
#include <filesystem>
// Utilities
#include <cstdlib>
#include <algorithm>
#include <numeric>
#include <utility>
#include <functional>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <ctime>
#include <chrono>
#include <random>
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
  VENDOR LIBRARIES
----------------------*/
#include <glm/glm.hpp>
#include <glm/matrix.hpp>

/*----------------------
  FLUGEL LIBRARY
----------------------*/

#include "util/utilities.hpp"
#include "util/logging/log.hpp"
#include "util/time/time.hpp"
#include "util/uuid.hpp"