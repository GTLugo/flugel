#pragma once

#ifdef FLUGEL_BUILD_DLL
  #ifdef _WIN32 // Windows
    #define FGE_API __declspec(dllexport)
  #elif __GNUC__ >= 4 // GCC
    #define FGE_API __attribute__((visibility("default")))
  #else // None
    #define FGE_API
  #endif
#else
  #ifdef _WIN32
    #define FGE_API __declspec(dllimport)
  #else // None
    #define FGE_API
  #endif
#endif

#if defined(DEBUG) || defined(RELDEB)
  #ifdef _WIN32 // Windows
      #define FGE_DEBUG_BREAK __debugbreak()
  #else
    #include <csignal>
    #ifdef SIGTRAP // POSIX
      #define FGE_DEBUG_BREAK raise(SIGTRAP)
    #else // Other
      #define FGE_DEBUG_BREAK raise(SIGABRT)
    #endif
  #endif
#else
  #define FGE_DEBUG_BREAK
#endif

#ifdef FLUGEL_ENABLE_ASSERTS
  #define FGE_ASSERT(x, ...) {\
    if(!(x)) {FGE_CRIT("FAILED ASSERT: {0}", __VA_ARGS__); FGE_DEBUG_BREAK; }\
  }
  #define FGE_ASSERT_ENG(x, ...) {\
    if(!(x)) {FGE_CRIT_ENG("FAILED ASSERT: {0}", __VA_ARGS__); FGE_DEBUG_BREAK; }\
  }
#else
  #define FLUGEL_ASSERT(x, ...)
  #define FLUGEL_ASSERT_E(x, ...)
#endif

#define BIT(x) (1 << x)

#define FGE_BIND(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); } 

namespace fge {
  // Scope = std::unique_ptr
  template<typename T, typename D = std::default_delete<T>>
  using Unique = std::unique_ptr<T, D>;
  template<typename T, typename... Args>
  constexpr Unique<T> makeUnique(Args&&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
  }

  // Ref = std::shared_ptr
  template<typename T>
  using Shared = std::shared_ptr<T>;
  template<typename T, typename... Args>
  constexpr Shared<T> makeShared(Args&&... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
  }
  
  template<typename T>
  using Weak = std::weak_ptr<T>;

  // Floating point
  using vector2_t = glm::dvec2;
  using vector3_t = glm::dvec3;
  using vector4_t = glm::dvec4;
  using matrix3_t = glm::dmat3;
  using matrix4_t = glm::dmat4;
  // Integer
  using ivector2_t = glm::ivec2;
  using ivector3_t = glm::ivec3;
  using ivector4_t = glm::ivec4;
  // Unsigned integer
  using uvector2_t = glm::uvec2;
  using uvector3_t = glm::uvec3;
  using uvector4_t = glm::uvec4;
}