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
  using WindowEvent = std::variant<std::monostate, WindowCloseEvent, WindowResizeEvent, WindowMovedEvent>;
  using InputEvent = std::variant<std::monostate, InputKeyEvent, InputMouseEvent, InputCursorEvent, InputScrollEvent>;

  using Event = std::variant<std::monostate, MainEvent, GameEvent, WindowEvent, InputEvent>;

  class EventSystem {
  public:
    using EventCallback = std::function<void(const Event&)>;

    static void init(EventCallback callback) {
      if (instance_) return;
      Log::trace_e("Initializing Event System...");
      instance_ = new EventSystem{};
      instance_->eventCallback_ = std::move(callback);
    }
    static void shutdown() { delete instance_; }

    static void handleEvent(const Event& e) {
      instance_->eventCallback_(e);
    }

    EventSystem(const EventSystem& other) = delete;
    EventSystem& operator=(const EventSystem& other) = delete;
  private:
    static inline EventSystem* instance_{nullptr};

    EventCallback eventCallback_;

//    static inline auto eventVisitor_ = EventVisitor{
//        [](const MainEvent&) {},
//        [](const GameEvent&) {},
//        [](const WindowCloseEvent&) {},
//        [](const WindowResizeEvent&) {},
//        [](const WindowMovedEvent&) {},
//        [](const InputKeyEvent&) {},
//        [](const InputMouseEvent&) {},
//        [](const InputCursorEvent&) {},
//        [](const InputScrollEvent&) {},
//        [](const auto&) {},
//    };

    EventSystem() = default;
    ~EventSystem() = default;
  };
}

