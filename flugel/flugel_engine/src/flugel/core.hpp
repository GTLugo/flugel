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
  #define FLUGEL_ASSERT_ENGINE(x, ...) {\
    if(!(x)) {FLUGEL_ERROR_ENGINE("FAILED ASSERT: {0}", __VA_ARGS__); DEBUG_BREAK; }\
  }
#else
  #define FLUGEL_ASSERT(x, ...)
  #define FLUGEL_ASSERT_ENGINE(x, ...)
#endif

#define BIT(x) (1 << x)