#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h> // to allow logging custom types using ostream<<

namespace ff {
  class Log {
  public:
    static void init();

    static std::shared_ptr<spdlog::logger>& engineLogger() { return engineLogger_; }
    static std::shared_ptr<spdlog::logger>& appLogger() { return appLogger_; }

    template<typename T>
    static inline void trace(const T& arg) {
      #if defined(DEBUG) or defined(RELDEB)
      appLogger()->trace(arg);
      #endif
    }

    template<typename T>
    static inline void trace_e(const T& arg) {
      #if defined(DEBUG) or defined(RELDEB)
      engineLogger()->trace(arg);
      #endif
    }

    template<typename... Args>
    static inline void trace(fmt::format_string<Args...> fmt, Args &&...args) {
      #if defined(DEBUG) or defined(RELDEB)
      appLogger()->trace(fmt, std::forward<Args>(args)...);
      #endif
    }

    template<typename... Args>
    static inline void trace_e(fmt::format_string<Args...> fmt, Args &&...args) {
      #if defined(DEBUG) or defined(RELDEB)
      engineLogger()->trace(fmt, std::forward<Args>(args)...);
      #endif
    }

    template<typename T>
    static inline void debug(const T& arg) {
      #if defined(DEBUG) or defined(RELDEB)
      appLogger()->debug(arg);
      #endif
    }

    template<typename T>
    static inline void debug_e(const T& arg) {
      #if defined(DEBUG) or defined(RELDEB)
      engineLogger()->debug(arg);
      #endif
    }

    template<typename... Args>
    static inline void debug(fmt::format_string<Args...> fmt, Args &&...args) {
      #if defined(DEBUG) or defined(RELDEB)
      appLogger()->debug(fmt, std::forward<Args>(args)...);
      #endif
    }

    template<typename... Args>
    static inline void debug_e(fmt::format_string<Args...> fmt, Args &&...args) {
      #if defined(DEBUG) or defined(RELDEB)
      engineLogger()->debug(fmt, std::forward<Args>(args)...);
      #endif
    }

    template<typename T>
    static inline void info(const T& arg) {
      #if defined(DEBUG) or defined(RELDEB)
      appLogger()->info(arg);
      #endif
    }

    template<typename T>
    static inline void info_e(const T& arg) {
      #if defined(DEBUG) or defined(RELDEB)
      engineLogger()->info(arg);
      #endif
    }

    template<typename... Args>
    static inline void info(fmt::format_string<Args...> fmt, Args &&...args) {
      #if defined(DEBUG) or defined(RELDEB)
      appLogger()->info(fmt, std::forward<Args>(args)...);
      #endif
    }

    template<typename... Args>
    static inline void info_e(fmt::format_string<Args...> fmt, Args &&...args) {
      #if defined(DEBUG) or defined(RELDEB)
      engineLogger()->info(fmt, std::forward<Args>(args)...);
      #endif
    }

    template<typename T>
    static inline void warning(const T& arg) {
      #if defined(DEBUG) or defined(RELDEB)
      appLogger()->warn(arg);
      #endif
    }

    template<typename T>
    static inline void warning_e(const T& arg) {
      #if defined(DEBUG) or defined(RELDEB)
      engineLogger()->warn(arg);
      #endif
    }

    template<typename... Args>
    static inline void warning(fmt::format_string<Args...> fmt, Args &&...args) {
      #if defined(DEBUG) or defined(RELDEB)
      appLogger()->warn(fmt, std::forward<Args>(args)...);
      #endif
    }

    template<typename... Args>
    static inline void warning_e(fmt::format_string<Args...> fmt, Args &&...args) {
      #if defined(DEBUG) or defined(RELDEB)
      engineLogger()->warn(fmt, std::forward<Args>(args)...);
      #endif
    }

    template<typename T>
    static inline void error(const T& arg) {
      #if defined(DEBUG) or defined(RELDEB)
      appLogger()->error(arg);
      #endif
    }

    template<typename T>
    static inline void error_e(const T& arg) {
      #if defined(DEBUG) or defined(RELDEB)
      engineLogger()->error(arg);
      #endif
    }

    template<typename... Args>
    static inline void error(fmt::format_string<Args...> fmt, Args &&...args) {
      #if defined(DEBUG) or defined(RELDEB)
      appLogger()->error(fmt, std::forward<Args>(args)...);
      #endif
    }

    template<typename... Args>
    static inline void error_e(fmt::format_string<Args...> fmt, Args &&...args) {
      #if defined(DEBUG) or defined(RELDEB)
      engineLogger()->error(fmt, std::forward<Args>(args)...);
      #endif
    }

    template<typename T>
    static inline void critical(const T& arg) {
      #if defined(DEBUG) or defined(RELDEB)
      appLogger()->critical(arg);
      #endif
    }

    template<typename T>
    static inline void critical_e(const T& arg) {
      #if defined(DEBUG) or defined(RELDEB)
      engineLogger()->critical(arg);
      #endif
    }

    template<typename... Args>
    static inline void critical(fmt::format_string<Args...> fmt, Args &&...args) {
      #if defined(DEBUG) or defined(RELDEB)
      appLogger()->critical(fmt, std::forward<Args>(args)...);
      #endif
    }

    template<typename... Args>
    static inline void critical_e(fmt::format_string<Args...> fmt, Args &&...args) {
      #if defined(DEBUG) or defined(RELDEB)
      engineLogger()->critical(fmt, std::forward<Args>(args)...);
      #endif
    }

  private:
    static inline std::shared_ptr<spdlog::logger> engineLogger_;
    static inline std::shared_ptr<spdlog::logger> appLogger_;
  };
}

//#if defined(DEBUG) or defined(RELDEB)
//  // Engine Log macros - Rated E for Engine!
//  #define Log::trace_e(...) ff::Log::engineLogger()->trace(__VA_ARGS__)
//  #define Log::debug_e(...) ff::Log::engineLogger()->debug(__VA_ARGS__)
//  #define FF_INFO_ENG(...)  ff::Log::engineLogger()->info(__VA_ARGS__)
//  #define FF_WARN_ENG(...)  ff::Log::engineLogger()->warn(__VA_ARGS__)
//  #define FF_ERROR_ENG(...) ff::Log::engineLogger()->error(__VA_ARGS__)
//  #define FF_CRIT_ENG(...)  ff::Log::engineLogger()->critical(__VA_ARGS__)
//  // App Log macros
//  #define FF_TRACE(...) ff::Log::appLogger()->trace(__VA_ARGS__)
//  #define FF_DEBUG(...) ff::Log::appLogger()->debug(__VA_ARGS__)
//  #define FF_INFO(...)  ff::Log::appLogger()->info(__VA_ARGS__)
//  #define FF_WARN(...)  ff::Log::appLogger()->warn(__VA_ARGS__)
//  #define FF_ERROR(...) ff::Log::appLogger()->error(__VA_ARGS__)
//  #define FF_CRIT(...)  ff::Log::appLogger()->critical(__VA_ARGS__)
//#elif defined(RELEASE) || defined(MINREL) // Disable logging macros on release builds
//  // Engine Log macros
//  #define Log::trace_e
//  #define Log::debug_e
//  #define FF_INFO_ENG
//  #define FF_WARN_ENG
//  #define FF_ERROR_ENG
//  #define FF_CRIT_ENG
//  // App Log macros
//  #define FF_TRACE
//  #define FF_DEBUG
//  #define FF_INFO
//  #define FF_WARN
//  #define FF_ERROR
//  #define FF_CRIT
//#endif