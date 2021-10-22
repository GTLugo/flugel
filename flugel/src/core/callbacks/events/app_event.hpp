#pragma once

#include "event.hpp"

namespace fge {
  enum class AppEventType {
    None = 0,
    StartMain, Poll,     UpdateMain,   EndMain,   // Main thread
    StartRender,         UpdateRender, EndRender, // Render thread
    StartGame, TickGame, UpdateGame,   EndGame,   // Game thread
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

  class FGE_API AppStartGameEvent : public AppEvent {
  public:
    AppStartGameEvent()
      : AppEvent{AppEventType::StartGame} {}

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <App> (START_GAME)";
      return ss.str();
    }
  };

  class FGE_API AppStartMainEvent : public AppEvent {
  public:
    AppStartMainEvent()
      : AppEvent{AppEventType::StartMain} {}

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <App> (START_MAIN)";
      return ss.str();
    }
  };

  class FGE_API AppStartRenderEvent : public AppEvent {
  public:
    AppStartRenderEvent()
      : AppEvent{AppEventType::StartRender} {}

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <App> (START_RENDER)";
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

  class FGE_API AppTickGameEvent : public AppEvent {
  public:
    AppTickGameEvent()
      : AppEvent{AppEventType::TickGame} {}

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <App> (TICK_GAME)";
      return ss.str();
    }
  };

  class FGE_API AppUpdateGameEvent : public AppEvent {
  public:
    AppUpdateGameEvent()
      : AppEvent{AppEventType::UpdateGame} {}

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <App> (UPDATE_GAME)";
      return ss.str();
    }
  };

  class FGE_API AppUpdateMainEvent : public AppEvent {
  public:
    AppUpdateMainEvent()
      : AppEvent{AppEventType::UpdateMain} {}

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <App> (UPDATE_MAIN)";
      return ss.str();
    }
  };

  class FGE_API AppUpdateRenderEvent : public AppEvent {
  public:
    AppUpdateRenderEvent()
      : AppEvent{AppEventType::UpdateRender} {}

    AppUpdateRenderEvent(const AppUpdateRenderEvent& e)
      : AppEvent{AppEventType::UpdateRender} {
      /// TODO: Complete copy constructor
    }

    AppUpdateRenderEvent& operator=(const AppUpdateRenderEvent& e) {
      /// TODO: Complete copy assignment
      return *this;
    }

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <App> (UPDATE_RENDER)";
      return ss.str();
    }
  };

  // class FGE_API AppTickEvent : public AppEvent {
  // public:
  //   AppTickEvent()
  //     : AppEvent{AppEventType::Tick} {}

  //   std::string toString() const override {
  //     std::stringstream ss;
  //     ss << "Event <App> (TICK)";
  //     return ss.str();
  //   }
  // };

  class FGE_API AppEndGameEvent : public AppEvent {
  public:
    AppEndGameEvent()
      : AppEvent{AppEventType::EndGame} {}

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <App> (END_GAME)";
      return ss.str();
    }
  };

  class FGE_API AppEndRenderEvent : public AppEvent {
  public:
    AppEndRenderEvent()
      : AppEvent{AppEventType::EndRender} {}

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <App> (END_RENDER)";
      return ss.str();
    }
  };

  class FGE_API AppEndMainEvent : public AppEvent {
  public:
    AppEndMainEvent()
      : AppEvent{AppEventType::EndMain} {}

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <App> (END_MAIN)";
      return ss.str();
    }
  };
}