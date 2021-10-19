#pragma once

#include "event.hpp"

namespace fge {
  enum class AppEventType {
    None = 0,
    Start, MainStart, RenderStart,
    Poll, FixedUpdate, MainUpdate, Update, RenderUpdate, Tick,
    End, MainEnd, RenderEnd,
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

  class FGE_API AppMainStartEvent : public AppEvent {
  public:
    AppMainStartEvent()
      : AppEvent{AppEventType::MainStart} {}

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <App> (MAIN_START)";
      return ss.str();
    }
  };

  class FGE_API AppRenderStartEvent : public AppEvent {
  public:
    AppRenderStartEvent()
      : AppEvent{AppEventType::RenderStart} {}

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <App> (RENDER_START)";
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

  class FGE_API AppFixedUpdateEvent : public AppEvent {
  public:
    AppFixedUpdateEvent()
      : AppEvent{AppEventType::FixedUpdate} {}

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <App> (FIXED_UPDATE)";
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

  class FGE_API AppMainUpdateEvent : public AppEvent {
  public:
    AppMainUpdateEvent()
      : AppEvent{AppEventType::MainUpdate} {}

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <App> (MAIN_UPDATE)";
      return ss.str();
    }
  };

  class FGE_API AppRenderUpdateEvent : public AppEvent {
  public:
    AppRenderUpdateEvent()
      : AppEvent{AppEventType::RenderUpdate} {}

    AppRenderUpdateEvent(const AppRenderUpdateEvent& e)
      : AppEvent{AppEventType::RenderUpdate} {
      /// TODO: Complete copy constructor
    }

    AppRenderUpdateEvent& operator=(const AppRenderUpdateEvent& e) {
      /// TODO: Complete copy assignment
      return *this;
    }

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <App> (RENDER_UPDATE)";
      return ss.str();
    }
  };

  class FGE_API AppTickEvent : public AppEvent {
  public:
    AppTickEvent()
      : AppEvent{AppEventType::Tick} {}

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <App> (TICK)";
      return ss.str();
    }
  };

  class FGE_API AppEndEvent : public AppEvent {
  public:
    AppEndEvent()
      : AppEvent{AppEventType::End} {}

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <App> (END)";
      return ss.str();
    }
  };

  class FGE_API AppRenderEndEvent : public AppEvent {
  public:
    AppRenderEndEvent()
      : AppEvent{AppEventType::RenderEnd} {}

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <App> (RENDER_END)";
      return ss.str();
    }
  };

  class FGE_API AppMainEndEvent : public AppEvent {
  public:
    AppMainEndEvent()
      : AppEvent{AppEventType::MainEnd} {}

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <App> (MAIN_END)";
      return ss.str();
    }
  };
}