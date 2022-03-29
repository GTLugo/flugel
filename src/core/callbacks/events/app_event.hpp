#pragma once

#include "event.hpp"

namespace ff {

  class AppEvent : public Event {
  public:
    enum Action { // Order of Main thread
      None = 0,
      Start, Stop,
      Poll, Update,
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
}