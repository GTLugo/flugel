#pragma once

#include <memory>

#include "core.hpp"
#include "spdlog/spdlog.h"

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
#define FGL_ENGINE_TRACE(...) ::Flugel::Log::getEngineLogger()->trace(__VA_ARGS__)
#define FGL_ENGINE_DEBUG(...) ::Flugel::Log::getEngineLogger()->debug(__VA_ARGS__)
#define FGL_ENGINE_INFO(...)  ::Flugel::Log::getEngineLogger()->info(__VA_ARGS__)
#define FGL_ENGINE_WARN(...)  ::Flugel::Log::getEngineLogger()->warn(__VA_ARGS__)
#define FGL_ENGINE_ERROR(...) ::Flugel::Log::getEngineLogger()->error(__VA_ARGS__)
#define FGL_ENGINE_CRIT(...)  ::Flugel::Log::getEngineLogger()->critical(__VA_ARGS__)
// App Log macros
#define FGL_TRACE(...) ::Flugel::Log::getAppLogger()->trace(__VA_ARGS__)
#define FGL_DEBUG(...) ::Flugel::Log::getAppLogger()->debug(__VA_ARGS__)
#define FGL_INFO(...)  ::Flugel::Log::getAppLogger()->info(__VA_ARGS__)
#define FGL_WARN(...)  ::Flugel::Log::getAppLogger()->warn(__VA_ARGS__)
#define FGL_ERROR(...) ::Flugel::Log::getAppLogger()->error(__VA_ARGS__)
#define FGL_CRIT(...)  ::Flugel::Log::getAppLogger()->critical(__VA_ARGS__)

// Disable logging macros on release builds
#if defined(RELEASE) || defined(MINREL)
// Engine Log macros
#define FGL_ENGINE_TRACE
#define FGL_ENGINE_DEBUG
#define FGL_ENGINE_INFO
#define FGL_ENGINE_WARN
#define FGL_ENGINE_ERROR
#define FGL_ENGINE_CRIT
// App Log macros
#define FGL_TRACE
#define FGL_DEBUG
#define FGL_INFO
#define FGL_WARN
#define FGL_ERROR
#define FGL_CRIT
#endif