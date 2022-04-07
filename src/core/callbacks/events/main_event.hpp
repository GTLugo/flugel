#pragma once

#include "event.hpp"

namespace ff {
  class MainEvent : public EventBase {
  public:
    enum Action { // Order of Main thread
      None = 0,
      Awake, Start, Stop,
      Poll, Update,
    };

    MainEvent(Action action) : action_{action} {}

    [[nodiscard]] EventBase::Type type() const override { return EventBase::Type::MainThread; }
    [[nodiscard]] Action action() const { return action_; }
    [[nodiscard]] std::string toString() const override {
      std::string name{"<MAIN> "};
      switch (action_) {
        case Action::Awake:  return name + "AWAKE";
        case Action::Start:  return name + "START";
        case Action::Poll:   return name + "POLL";
        case Action::Update: return name + "UPDATE";
        case Action::Stop:   return name + "STOP";
        default:             return name + "UNKNOWN";
      }
    }
  protected:
    const Action action_;
  };
}