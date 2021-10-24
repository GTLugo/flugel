#pragma once

#include "event.hpp"

namespace fge {
  enum class LogicEventType {
    None = 0,
    Start, Tick, Update, Stop, // Game thread
  };

  class FGE_API LogicEvent : public Event {
  public:
    EVENT_CATEGORY(EventCategory::Logic)

    LogicEventType type() const { return type_; }
  protected:
    const LogicEventType type_;
    
    LogicEvent(LogicEventType type)
      : type_{type} {}
  };

  class FGE_API LogicStartEvent : public LogicEvent {
  public:
    LogicStartEvent()
      : LogicEvent{LogicEventType::Start} {}

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <Logic> (START)";
      return ss.str();
    }
  };

  class FGE_API LogicTickEvent : public LogicEvent {
  public:
    LogicTickEvent()
      : LogicEvent{LogicEventType::Tick} {}

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <Logic> (TICK)";
      return ss.str();
    }
  };

  class FGE_API LogicUpdateEvent : public LogicEvent {
  public:
    LogicUpdateEvent()
      : LogicEvent{LogicEventType::Update} {}

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <Logic> (UPDATE)";
      return ss.str();
    }
  };

  class FGE_API LogicStopEvent : public LogicEvent {
  public:
    LogicStopEvent()
      : LogicEvent{LogicEventType::Stop} {}

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <Logic> (STOP)";
      return ss.str();
    }
  };
}