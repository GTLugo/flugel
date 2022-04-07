#pragma once

#include "event.hpp"

namespace ff {
  class GameEvent : public EventBase {
  public:
    enum Action { // Order of Main thread
      None = 0,
      Awake, Start, Stop,
      Tick, Update,
      RenderBegin, RenderGame, RenderImGui, RenderEnd,
    };

    GameEvent(Action action) : action_{action} {}

    [[nodiscard]] EventBase::Type type() const override { return EventBase::Type::GameThread; }
    [[nodiscard]] Action action() const { return action_; }
    [[nodiscard]] std::string toString() const override {
      std::string name{"<GAME> "};
      switch (action_) {
        case Action::Awake:       return name + "AWAKE";
        case Action::Start:       return name + "START";
        case Action::Tick:        return name + "TICK";
        case Action::Update:      return name + "UPDATE";
        case Action::RenderBegin: return name + "RENDER_BEGIN";
        case Action::RenderGame:  return name + "RENDER_GAME";
        case Action::RenderImGui: return name + "RENDER_IMGUI";
        case Action::RenderEnd:   return name + "RENDER_END";
        case Action::Stop:        return name + "STOP";
        default:                  return name + "UNKNOWN";
      }
    }
  protected:
    const Action action_;
  };
}