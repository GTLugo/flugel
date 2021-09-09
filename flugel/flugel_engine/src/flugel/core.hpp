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

#define BIT(x) (1 << x)