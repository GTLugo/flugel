#pragma once

#include "event.hpp"

namespace fge {

  class FGE_API AppEvent : public Event {
  public:
    enum Action {
      None = 0,
      Start, Poll, Update, Stop, // Main thread
    };

    explicit AppEvent(Action A)
      : action_{A} {}

    EVENT_TYPE(Event::Type::App)

    [[nodiscard]] Action action() const { return action_; }

    [[nodiscard]] std::string toString() const override {
      std::stringstream ss;
      ss << "Event <App> ";
      switch (action_) {
        case Action::Start:
          ss << "(START)";
          break;
        case Action::Poll:
          ss << "(POLL)";
          break;
        case Action::Update:
          ss << "(UPDATE)";
          break;
        case Action::Stop:
          ss << "(STOP)";
          break;
        default:
          ss << "(UNKNOWN)";
          break;
      }
      return ss.str();
    }
  protected:
    const Action action_;
  };

//  class FGE_API AppStartEvent : public AppEvent {
//  public:
//    AppStartEvent()
//      : AppEvent{AppEventType::Start} {}
//
//    std::string toString() const override {
//      std::stringstream ss;
//      ss << "Event <App> (START)";
//      return ss.str();
//    }
//  };
//
//  class FGE_API AppPollEvent : public AppEvent {
//  public:
//    AppPollEvent()
//      : AppEvent{AppEventType::Poll} {}
//
//    std::string toString() const override {
//      std::stringstream ss;
//      ss << "Event <App> (POLL)";
//      return ss.str();
//    }
//  };
//
//  class FGE_API AppUpdateEvent : public AppEvent {
//  public:
//    AppUpdateEvent()
//      : AppEvent{AppEventType::Update} {}
//
//    std::string toString() const override {
//      std::stringstream ss;
//      ss << "Event <App> (UPDATE)";
//      return ss.str();
//    }
//  };
//
//  class FGE_API AppStopEvent : public AppEvent {
//  public:
//    AppStopEvent()
//      : AppEvent{AppEventType::Stop} {}
//
//    std::string toString() const override {
//      std::stringstream ss;
//      ss << "Event <App> (STOP)";
//      return ss.str();
//    }
//  };
}