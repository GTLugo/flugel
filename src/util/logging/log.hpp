#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h> // to allow logging custom types using ostream<<

namespace fge {
  class FGE_API Log {
  public:
      static void init();

      static std::shared_ptr<spdlog::logger>& engineLogger() { return engineLogger_; }
      static std::shared_ptr<spdlog::logger>& appLogger() { return appLogger_; }

  private:
    static inline std::shared_ptr<spdlog::logger> engineLogger_;
    static inline std::shared_ptr<spdlog::logger> appLogger_;
  };
}

#if defined(DEBUG) || defined(RELDEB)
  // Engine Log macros - Rated E for Engine!
  #define FGE_TRACE_ENG(...) fge::Log::engineLogger()->trace(__VA_ARGS__)
  #define FGE_DEBUG_ENG(...) fge::Log::engineLogger()->debug(__VA_ARGS__)
  #define FGE_INFO_ENG(...)  fge::Log::engineLogger()->info(__VA_ARGS__)
  #define FGE_WARN_ENG(...)  fge::Log::engineLogger()->warn(__VA_ARGS__)
  #define FGE_ERROR_ENG(...) fge::Log::engineLogger()->error(__VA_ARGS__)
  #define FGE_CRIT_ENG(...)  fge::Log::engineLogger()->critical(__VA_ARGS__)
  // App Log macros
  #define FGE_TRACE(...) fge::Log::appLogger()->trace(__VA_ARGS__)
  #define FGE_DEBUG(...) fge::Log::appLogger()->debug(__VA_ARGS__)
  #define FGE_INFO(...)  fge::Log::appLogger()->info(__VA_ARGS__)
  #define FGE_WARN(...)  fge::Log::appLogger()->warn(__VA_ARGS__)
  #define FGE_ERROR(...) fge::Log::appLogger()->error(__VA_ARGS__)
  #define FGE_CRIT(...)  fge::Log::appLogger()->critical(__VA_ARGS__)
#elif defined(RELEASE) || defined(MINREL) // Disable logging macros on release builds
  // Engine Log macros
  #define FGE_TRACE_ENG
  #define FGE_DEBUG_ENG
  #define FGE_INFO_ENG
  #define FGE_WARN_ENG
  #define FGE_ERROR_ENG
  #define FGE_CRIT_ENG
  // App Log macros
  #define FGE_TRACE
  #define FGE_DEBUG
  #define FGE_INFO
  #define FGE_WARN
  #define FGE_ERROR
  #define FGE_CRIT
#endif