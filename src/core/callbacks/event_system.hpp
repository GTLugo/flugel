//
// Created by galex on 3/27/2022.
//

#pragma once

#include "core/callbacks/events/event.hpp"
#include "core/callbacks/events/main_event.hpp"
#include "core/callbacks/events/game_event.hpp"
#include "core/callbacks/events/window_event.hpp"
#include "core/callbacks/events/input_event.hpp"

namespace ff {
  template<class... T>
  struct EventVisitor : T... {
    using T::operator()...;
  };
  template<class... T> EventVisitor(T...) -> EventVisitor<T...>;

  using MainEvent = std::variant<std::monostate, MainAwakeEvent, MainStartEvent, MainPollEvent, MainUpdateEvent, MainStopEvent>;
  using GameEvent = std::variant<std::monostate, GameAwakeEvent, GameStartEvent, GameTickEvent, GameUpdateEvent,
      GameBeginFrameEvent, GameDrawEvent, GameImGuiEvent, GameEndFrameEvent, GameStopEvent>;
  using WindowEvent = std::variant<std::monostate, WindowCloseEvent, WindowResizeEvent, WindowMovedEvent, WindowFocusEvent>;
  using InputEvent = std::variant<std::monostate, InputKeyEvent, InputMouseEvent, InputCursorEvent, InputScrollEvent>;

  using Event = std::variant<std::monostate, MainEvent, GameEvent, WindowEvent, InputEvent>;

  class EventManager {
  public:
    using EventCallback = std::function<void(const Event&)>;

    static void init(EventCallback callback) {
      if (instance_) return;
      Log::trace_e("Initializing Event System...");
      instance_ = new EventManager{};
      instance_->eventCallback_ = std::move(callback);
    }
    static void shutdown() { delete instance_; }

    static void submit(const Event& e) {
      instance_->eventCallback_(e);
    }

    template<class E, class... Args>
    static auto visit(E event, Args... args) {
      return std::visit(EventVisitor{
          ((args, ...))
      }, event);
    }

    EventManager(const EventManager& other) = delete;
    EventManager& operator=(const EventManager& other) = delete;
  private:
    static inline EventManager* instance_{nullptr};

    EventCallback eventCallback_;

    EventManager() = default;
    ~EventManager() = default;
  };
}

