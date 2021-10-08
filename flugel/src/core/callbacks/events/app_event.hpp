#pragma once

#include "event.hpp"

namespace Flugel {
  enum class AppEventType {
    None = 0,
    Start, Poll, Tick, UpdateFixed, Update, Render, End,
  };

  class FLUGEL_API AppEvent : public Event {
  public:
    EVENT_CATEGORY(App)

    AppEventType type() const { return type_; }
  protected:
    const AppEventType type_;
    
    AppEvent(AppEventType type)
      : type_{type} {}
  };

  class FLUGEL_API AppStartEvent : public AppEvent {
  public:
    AppStartEvent()
     : AppEvent{AppEventType::Start} {}

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <App> (START)";
      return ss.str();
    }
  };

  class FLUGEL_API AppPollEvent : public AppEvent {
  public:
    AppPollEvent()
     : AppEvent{AppEventType::Poll} {}

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <App> (POLL)";
      return ss.str();
    }
  };

  class FLUGEL_API AppTickEvent : public AppEvent {
  public:
    AppTickEvent()
     : AppEvent{AppEventType::Tick} {}

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <App> (TICK)";
      return ss.str();
    }
  };

  class FLUGEL_API AppUpdateFixedEvent : public AppEvent {
  public:
    AppUpdateFixedEvent()
     : AppEvent{AppEventType::UpdateFixed} {}

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <App> (UPDATE_FIXED)";
      return ss.str();
    }
  };

  class FLUGEL_API AppUpdateEvent : public AppEvent {
  public:
    AppUpdateEvent()
     : AppEvent{AppEventType::Update} {}

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <App> (UPDATE)";
      return ss.str();
    }
  };

  class FLUGEL_API AppRenderEvent : public AppEvent {
  public:
    AppRenderEvent()
     : AppEvent{AppEventType::Render} {}

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <App> (RENDER)";
      return ss.str();
    }
  };

  class FLUGEL_API AppEndEvent : public AppEvent {
  public:
    AppEndEvent()
     : AppEvent{AppEventType::End} {}

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <App> (END)";
      return ss.str();
    }
  };
}