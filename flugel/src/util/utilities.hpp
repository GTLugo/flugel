#pragma once

#ifdef FLUGEL_DYNAMIC
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
#else
  #define FGE_API
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
  #define FGE_ASSERT(x, ...)
  #define FGE_ASSERT_ENG(x, ...)
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

  using i8  = std::int8_t;
  using i16 = std::int16_t;
  using i32 = std::int32_t;
  using i64 = std::int64_t;
  using u8  = std::uint8_t;
  using u16 = std::uint16_t;
  using u32 = std::uint32_t;
  using u64 = std::uint64_t;

  using i128 = boost::multiprecision::int128_t;
  using u128 = boost::multiprecision::uint128_t;

  // Floating point single precision
  using vec2 = glm::vec2;
  using vec3 = glm::vec3;
  using vec4 = glm::vec4;
  using mat3 = glm::mat3;
  using mat4 = glm::mat4;
  // Floating point double precision
  using dvec2 = glm::dvec2;
  using dvec3 = glm::dvec3;
  using dvec4 = glm::dvec4;
  using dmat3 = glm::dmat3;
  using dmat4 = glm::dmat4;
  // Integer
  using ivec2 = glm::ivec2;
  using ivec3 = glm::ivec3;
  using ivec4 = glm::ivec4;
  // Unsigned integer
  using uvec2 = glm::uvec2;
  using uvec3 = glm::uvec3;
  using uvec4 = glm::uvec4;
}