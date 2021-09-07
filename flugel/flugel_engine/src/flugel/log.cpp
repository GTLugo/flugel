#include "log.hpp"

#include "spdlog/pattern_formatter.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Flugel {
  class level_formatter_flag : public spdlog::custom_flag_formatter {
  public:
    void format(const spdlog::details::log_msg& msg, const std::tm& tm, spdlog::memory_buf_t& dest) override {
      std::string some_txt{"[NULL]"};
      switch (msg.level) {
      case spdlog::level::trace:    some_txt = "[TRCE]"; break;
      case spdlog::level::debug:    some_txt = "[DEBG]"; break;
      case spdlog::level::info:     some_txt = "[INFO]"; break;
      case spdlog::level::warn:     some_txt = "[WARN]"; break;
      case spdlog::level::err:      some_txt = "[ERRO]"; break;
      case spdlog::level::critical: some_txt = "[CRIT]"; break;
      default: break;
      };
      dest.append(some_txt.data(), some_txt.data() + some_txt.size());
    }

    std::unique_ptr<custom_flag_formatter> clone() const override {
      return spdlog::details::make_unique<level_formatter_flag>();
    }
  };

  class file_formatter_flag : public spdlog::custom_flag_formatter {
  public:
    void format(const spdlog::details::log_msg& msg, const std::tm& tm, spdlog::memory_buf_t& dest) override {
      std::string some_txt{msg.source.filename};
      some_txt.push_back(':');
      some_txt.append(std::to_string(msg.source.line));
      dest.append(some_txt.data(), some_txt.data() + some_txt.size());
    }

    std::unique_ptr<custom_flag_formatter> clone() const override {
      return spdlog::details::make_unique<file_formatter_flag>();
    }
  };

  std::shared_ptr<spdlog::logger> Log::engineLogger_;
  std::shared_ptr<spdlog::logger> Log::appLogger_;

  void Log::init() {
    auto formatter = std::make_unique<spdlog::pattern_formatter>();
    formatter->add_flag<level_formatter_flag>('*')
      .add_flag<file_formatter_flag>('N')
      .set_pattern("%T %^%7*%$ %n: %v");
    spdlog::set_formatter(std::move(formatter));
    
    engineLogger_ = spdlog::stdout_color_mt("FLUGEL");
    engineLogger_->set_level(spdlog::level::trace);
    
    appLogger_ = spdlog::stdout_color_mt("APP");
    appLogger_->set_level(spdlog::level::trace);
  }
}