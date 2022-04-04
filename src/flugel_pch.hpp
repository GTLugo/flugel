#pragma once
/*----------------------
  STD LIBRARY
----------------------*/

// IO
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <filesystem>
// Utilities
#include <cstdlib>
#include <algorithm>
#include <numeric>
#include <utility>
#include <functional>
#include <memory>
#include <ranges>
#include <future>
#include <ctime>
#include <chrono>
#include <random>
#include <stdexcept>
#include <limits>
#include <typeinfo>
#include <format>
#include <string_view>
// Threading
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <stop_token>
// Data Structures
#include <bitset>
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
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/functional/hash.hpp>
#include <boost/algorithm/clamp.hpp>
#include <boost/random.hpp>
#include <boost/nondet_random.hpp>

/*----------------------
  FLUGEL LIBRARY
----------------------*/

#include "util/types.hpp"
#include "util/utilities.hpp"
#include "util/logging/log.hpp"
#include "util/time.hpp"
#include "util/random.hpp"
//#include "util/uuid.hpp"
#include "util/color/color.hpp"