#pragma once

#if defined(DEBUG) or defined(RELDEB)
  #ifdef _WIN32 // Windows
      #define FF_DEBUG_BREAK __debugbreak()
  #else
    #include <csignal>
    #ifdef SIGTRAP // POSIX
      #define FF_DEBUG_BREAK raise(SIGTRAP)
    #else // Other
      #define FF_DEBUG_BREAK raise(SIGABRT)
    #endif
  #endif
#else
  #define FF_DEBUG_BREAK
#endif

#ifdef FLUGEL_ENABLE_ASSERTS
  #define FF_ASSERT(x, ...) {\
    if(!(x)) {Log::critical("FAILED ASSERT: {0}", __VA_ARGS__); FF_DEBUG_BREAK; }\
  }
  #define FF_ASSERT_E(x, ...) {\
    if(!(x)) {Log::critical_e("FAILED ASSERT: {0}", __VA_ARGS__); FF_DEBUG_BREAK; }\
  }
#else
  #define FF_ASSERT(x, ...)
  #define FF_ASSERT_E(x, ...)
#endif

#define BIT(x) (1 << x)

#define FF_BIND_AS_LAMBDA(fn) [this](auto&&... args) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace ff {
  template<typename T, typename D = std::default_delete<T>>
  using Unique = std::unique_ptr<T, D>;
  template<typename T, typename... Args>
  constexpr Unique<T> makeUnique(Args&&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
  }

  template<typename T>
  using Shared = std::shared_ptr<T>;
  template<typename T, typename... Args>
  constexpr Shared<T> makeShared(Args&&... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
  }
  
  template<typename T>
  using Weak = std::weak_ptr<T>;
}