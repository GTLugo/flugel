#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h" // to allow logging custom types using ostream<<

namespace Flugel {
  class FLUGEL_API Log {
  public:
      static void init();

      inline static std::shared_ptr<spdlog::logger>& getEngineLogger() { return engineLogger_; }
      inline static std::shared_ptr<spdlog::logger>& getAppLogger() { return appLogger_; }

  private:
    static std::shared_ptr<spdlog::logger> engineLogger_;
    static std::shared_ptr<spdlog::logger> appLogger_;
  };
}

// Engine Log macros
#define FLUGEL_TRACE_ENGINE(...) Flugel::Log::getEngineLogger()->trace(__VA_ARGS__)
#define FLUGEL_DEBUG_ENGINE(...) Flugel::Log::getEngineLogger()->debug(__VA_ARGS__)
#define FLUGEL_INFO_ENGINE(...)  Flugel::Log::getEngineLogger()->info(__VA_ARGS__)
#define FLUGEL_WARN_ENGINE(...)  Flugel::Log::getEngineLogger()->warn(__VA_ARGS__)
#define FLUGEL_ERROR_ENGINE(...) Flugel::Log::getEngineLogger()->error(__VA_ARGS__)
#define FLUGEL_CRIT_ENGINE(...)  Flugel::Log::getEngineLogger()->critical(__VA_ARGS__)
// App Log macros
#define FLUGEL_TRACE(...) Flugel::Log::getAppLogger()->trace(__VA_ARGS__)
#define FLUGEL_DEBUG(...) Flugel::Log::getAppLogger()->debug(__VA_ARGS__)
#define FLUGEL_INFO(...)  Flugel::Log::getAppLogger()->info(__VA_ARGS__)
#define FLUGEL_WARN(...)  Flugel::Log::getAppLogger()->warn(__VA_ARGS__)
#define FLUGEL_ERROR(...) Flugel::Log::getAppLogger()->error(__VA_ARGS__)
#define FLUGEL_CRIT(...)  Flugel::Log::getAppLogger()->critical(__VA_ARGS__)

// Disable logging macros on release builds
#if defined(RELEASE) || defined(MINREL)
// Engine Log macros
#define FLUGEL_TRACE_ENGINE
#define FLUGEL_DEBUG_ENGINE
#define FLUGEL_INFO_ENGINE
#define FLUGEL_WARN_ENGINE
#define FLUGEL_ERROR_ENGINE
#define FLUGEL_CRIT_ENGINE
// App Log macros
#define FLUGEL_TRACE
#define FLUGEL_DEBUG
#define FLUGEL_INFO
#define FLUGEL_WARN
#define FLUGEL_ERROR
#define FLUGEL_CRIT
#endif