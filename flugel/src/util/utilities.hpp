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

  // Floating point single precision
  using fvector2_t = glm::vec2;
  using fvector3_t = glm::vec3;
  using fvector4_t = glm::vec4;
  using fmatrix3_t = glm::mat3;
  using fmatrix4_t = glm::mat4;
  // Floating point double precision
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