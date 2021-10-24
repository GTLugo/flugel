#pragma once

#include "event.hpp"

namespace fge {
  enum class AppEventType {
    None = 0,
    Start, Poll, Update, Stop, // Main thread
  };

  class FGE_API AppEvent : public Event {
  public:
    EVENT_CATEGORY(EventCategory::App)

    AppEventType type() const { return type_; }
  protected:
    const AppEventType type_;
    
    AppEvent(AppEventType type)
      : type_{type} {}
  };

  class FGE_API AppStartEvent : public AppEvent {
  public:
    AppStartEvent()
      : AppEvent{AppEventType::Start} {}

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <App> (START)";
      return ss.str();
    }
  };

  class FGE_API AppPollEvent : public AppEvent {
  public:
    AppPollEvent()
      : AppEvent{AppEventType::Poll} {}

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <App> (POLL)";
      return ss.str();
    }
  };

  class FGE_API AppUpdateEvent : public AppEvent {
  public:
    AppUpdateEvent()
      : AppEvent{AppEventType::Update} {}

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <App> (UPDATE)";
      return ss.str();
    }
  };

  class FGE_API AppStopEvent : public AppEvent {
  public:
    AppStopEvent()
      : AppEvent{AppEventType::Stop} {}

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <App> (STOP)";
      return ss.str();
    }
  };
}