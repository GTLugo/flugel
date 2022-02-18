#pragma once

#include "event.hpp"

namespace fge {

  class FGE_API LogicEvent : public Event {
  public:
    enum Action {
      None = 0,
      Start, Tick, Update, Stop, // Game thread
    };

    explicit LogicEvent(Action action)
        : action_{action} {}

    EVENT_TYPE(Event::Type::Logic)

    [[nodiscard]] Action action() const { return action_; }

    [[nodiscard]] std::string toString() const override {
      std::stringstream ss;
      ss << "Event <Logic> ";
      switch (action_) {
        case Action::Start:
          ss << "(START)";
          break;
        case Action::Tick:
          ss << "(TICK)";
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