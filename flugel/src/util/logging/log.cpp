#include "log.hpp"

#include <spdlog/pattern_formatter.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>

namespace fge {
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
  
  std::shared_ptr<spdlog::logger> Log::engineLogger_;
  std::shared_ptr<spdlog::logger> Log::appLogger_;

  void Log::init() {
    auto formatter = std::make_unique<spdlog::pattern_formatter>();
    formatter->add_flag<level_formatter_flag>('*').set_pattern("%T %^%7*%$ %n: %v");
    
    auto commonSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/common.log", 1048576 * 5, 3);

    std::vector<spdlog::sink_ptr> flugelSinks;
    flugelSinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
    flugelSinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/flugel.log", 1048576 * 5, 3));
    flugelSinks.push_back(commonSink);
    engineLogger_ = std::make_shared<spdlog::logger>("FLUGEL", flugelSinks.begin(), flugelSinks.end());
    for (auto& sink : engineLogger_->sinks()) {
      sink->set_formatter(formatter->clone());
    }

    std::vector<spdlog::sink_ptr> appSinks;
    appSinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
    appSinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/app.log", 1048576 * 5, 3));
    appSinks.push_back(commonSink);
    appLogger_ = std::make_shared<spdlog::logger>("APP", appSinks.begin(), appSinks.end());
    for (auto& sink : appLogger_->sinks()) {
      sink->set_formatter(formatter->clone());
    }

    //engineLogger_ = spdlog::stdout_color_mt("FLUGEL");
    //appLogger_ = spdlog::stdout_color_mt("APP");

    engineLogger_->set_level(spdlog::level::trace);
    appLogger_->set_level(spdlog::level::trace);

    FGE_INFO_ENG("Initialized engine logger!");
    FGE_INFO("Initialized app logger!");
  }
}