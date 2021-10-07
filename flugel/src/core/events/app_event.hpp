#pragma once

#include "notifier.hpp"

namespace Flugel {
  enum class AppEventType {
    None = 0,
    Start, Tick, UpdateFixed, Update, Render, End,
  };

  class FLUGEL_API AppEvent : public Event {
  public:
    EVENT_CATEGORY(App)

    AppEvent(AppEventType type)
      : type_{type} {}

    AppEventType type() const { return type_; }
    
    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <App> (";
      switch (type_) {
        case AppEventType::Start: {
          ss << "START)";
          break;
        }
        case AppEventType::Tick: {
          ss << "TICK)";
          break;
        }
        case AppEventType::UpdateFixed: {
          ss << "UPDATE_FIXED)";
          break;
        }
        case AppEventType::Update: {
          ss << "UPDATE)";
          break;
        }
        case AppEventType::Render: {
          ss << "RENDER)";
          break;
        }
        case AppEventType::End: {
          ss << "END)";
          break;
        }
        default: {
          ss << "NULL)";
          break;
        }
      }
      return ss.str();
    }
  protected:
    AppEventType type_;
  };
}