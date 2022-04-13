#pragma once

#include "event.hpp"

namespace ff {
  class MainEventBase : public EventBase {
  public:
    [[nodiscard]] std::string toString() const override { return "<MAIN>"; }
  };

  class MainAwakeEvent : public MainEventBase {
  public:
    MainAwakeEvent() = default;
    [[nodiscard]] std::string toString() const override { return MainEventBase::toString() + " Awake"; }
  };

  class MainStartEvent : public MainEventBase {
  public:
    MainStartEvent() = default;
    [[nodiscard]] std::string toString() const override { return MainEventBase::toString() + " Start"; }
  };

  class MainPollEvent : public MainEventBase {
  public:
    MainPollEvent() = default;
    [[nodiscard]] std::string toString() const override { return MainEventBase::toString() + " Poll"; }
  };

  class MainUpdateEvent : public MainEventBase {
  public:
    MainUpdateEvent() = default;
    [[nodiscard]] std::string toString() const override { return MainEventBase::toString() + " Update"; }
  };

  class MainStopEvent : public MainEventBase {
  public:
    MainStopEvent() = default;
    [[nodiscard]] std::string toString() const override { return MainEventBase::toString() + " Stop"; }
  };
}