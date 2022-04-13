#pragma once

#include "event.hpp"

namespace ff {
  class GameEventBase : public EventBase {
  public:
    [[nodiscard]] std::string toString() const override { return "<GAME>"; }
  };

  class GameAwakeEvent : public GameEventBase {
  public:
    GameAwakeEvent() = default;
    [[nodiscard]] std::string toString() const override { return GameEventBase::toString() + " Awake"; }
  };

  class GameStartEvent : public GameEventBase {
  public:
    GameStartEvent() = default;
    [[nodiscard]] std::string toString() const override { return GameEventBase::toString() + " Start"; }
  };

  class GameTickEvent : public GameEventBase {
  public:
    GameTickEvent() = default;
    [[nodiscard]] std::string toString() const override { return GameEventBase::toString() + " Tick"; }
  };

  class GameUpdateEvent : public GameEventBase {
  public:
    GameUpdateEvent() = default;
    [[nodiscard]] std::string toString() const override { return GameEventBase::toString() + " Update"; }
  };

  class GameBeginFrameEvent : public GameEventBase {
  public:
    GameBeginFrameEvent() = default;
    [[nodiscard]] std::string toString() const override { return GameEventBase::toString() + " Begin Frame"; }
  };

  class GameDrawEvent : public GameEventBase {
  public:
    GameDrawEvent() = default;
    [[nodiscard]] std::string toString() const override { return GameEventBase::toString() + " Draw"; }
  };

  class GameImGuiEvent : public GameEventBase {
  public:
    GameImGuiEvent() = default;
    [[nodiscard]] std::string toString() const override { return GameEventBase::toString() + " ImGui"; }
  };

  class GameEndFrameEvent : public GameEventBase {
  public:
    GameEndFrameEvent() = default;
    [[nodiscard]] std::string toString() const override { return GameEventBase::toString() + " End Frame"; }
  };

  class GameStopEvent : public GameEventBase {
  public:
    GameStopEvent() = default;
    [[nodiscard]] std::string toString() const override { return GameEventBase::toString() + " Stop"; }
  };
}