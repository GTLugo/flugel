//
// Created by galex on 4/2/2022.
//

#pragma once

#include "core/callbacks/events/event.hpp"
#include "core/callbacks/events/app_event.hpp"
#include "core/callbacks/events/render_event.hpp"
#include "core/callbacks/events/logic_event.hpp"
#include "core/callbacks/events/window_event.hpp"
#include "core/callbacks/events/keyboard_event.hpp"
#include "core/callbacks/events/mouse_event.hpp"

#include "core/callbacks/notifier/notifier.hpp"

namespace ff {
  template<class C>
  class Subscribable {
  public:
    class AppEventSubscriber {
    public:
      explicit AppEventSubscriber(C* object)
          : object_{object},
            id_{object->template subscribe<AppEvent>(FF_LAMBDA(onAppEvent))}{
        Log::debug_e("Subscribed: <AppEvent> {1}", id_);
      }
      ~AppEventSubscriber() {
        Log::debug_e("Unsubscribed: <AppEvent> {1}", id_);
        object_->template unsubscribe<AppEvent>(id_);
      }
    protected:
      virtual bool onAppEvent(const AppEvent& e) { return false; }
    private:
      C* object_;
      UUID id_;
    };

    class RenderEventSubscriber {
    public:
      explicit RenderEventSubscriber(C* object)
          : object_{object},
            id_{object->template subscribe<RenderEvent>(FF_LAMBDA(onRenderEvent))} {
        Log::debug_e("Subscribed: <RenderEvent> {1}", id_);
      }
      ~RenderEventSubscriber() {
        Log::debug_e("Unsubscribed: <RenderEvent> {1}", id_);
        object_->template unsubscribe<RenderEvent>(id_);
      }
    protected:
      virtual bool onRenderEvent(const RenderEvent& e) { return false; }
    private:
      C* object_;
      UUID id_;
    };

    class LogicEventSubscriber {
    public:
      explicit LogicEventSubscriber(C* object)
          : object_{object},
            id_{object->template subscribe<LogicEvent>(FF_LAMBDA(onLogicEvent))} {
        Log::debug_e("Subscribed: <LogicEvent> {1}", id_);
      }
      ~LogicEventSubscriber() {
        Log::debug_e("Unsubscribed: <LogicEvent> {1}", id_);
        object_->template unsubscribe<LogicEvent>(id_);
      }
    protected:
      virtual bool onLogicEvent(const LogicEvent& e) { return false; }
    private:
      C* object_;
      UUID id_;
    };

    class WindowEventSubscriber {
    public:
      explicit WindowEventSubscriber(C* object)
          : object_{object},
            id_{object->template subscribe<WindowEvent>(FF_LAMBDA(onWindowEvent))} {
        Log::debug_e("Subscribed: <WindowEvent> {1}", id_);
      }
      ~WindowEventSubscriber() {
        Log::debug_e("Unsubscribed: <WindowEvent> {1}", id_);
        object_->template unsubscribe<WindowEvent>(id_);
      }
    protected:
      virtual bool onWindowEvent(const WindowEvent& e) { return false; }
    private:
      C* object_;
      UUID id_;
    };

    class KeyboardEventSubscriber {
    public:
      explicit KeyboardEventSubscriber(C* object)
          : object_{object},
            id_{object->template subscribe<KeyboardEvent>(FF_LAMBDA(onKeyboardEvent))} {
        Log::debug_e("Subscribed: <KeyboardEvent> {1}", id_);
      }
      ~KeyboardEventSubscriber() {
        Log::debug_e("Unsubscribed: <KeyboardEvent> {1}", id_);
        object_->template unsubscribe<KeyboardEvent>(id_);
      }
    protected:
      virtual bool onKeyboardEvent(const KeyboardEvent& e) { return false; }
    private:
      C* object_;
      UUID id_;
    };

    class MouseEventSubscriber {
    public:
      explicit MouseEventSubscriber(C* object)
          : object_{object},
            id_{object->template subscribe<MouseEvent>(FF_LAMBDA(onMouseEvent))} {
        Log::debug_e("Subscribed: <MouseEvent> {1}", id_);
      }
      ~MouseEventSubscriber() {
        Log::debug_e("Unsubscribed: <MouseEvent> {1}", id_);
        object_->template unsubscribe<MouseEvent>(id_);
      }
    protected:
      virtual bool onMouseEvent(const MouseEvent& e) { return false; }
    private:
      C* object_;
      UUID id_;
    };

    class CursorEventSubscriber {
    public:
      explicit CursorEventSubscriber(C* object)
          : object_{object},
            id_{object->template subscribe<CursorEvent>(FF_LAMBDA(onCursorEvent))} {
        Log::debug_e("Subscribed: <CursorEvent> {1}", id_);
      }
      ~CursorEventSubscriber() {
        Log::debug_e("Unsubscribed: <CursorEvent> {1}", id_);
        object_->template unsubscribe<CursorEvent>(id_);
      }
    protected:
      virtual bool onCursorEvent(const CursorEvent& e) { return false; }
    private:
      C* object_;
      UUID id_;
    };

    class ScrollEventSubscriber {
    public:
      explicit ScrollEventSubscriber(C* object)
          : object_{object},
            id_{object->template subscribe<ScrollEvent>(FF_LAMBDA(onScrollEvent))} {
        Log::debug_e("Subscribed: <ScrollEvent> {1}", id_);
      }
      ~ScrollEventSubscriber() {
        Log::debug_e("Unsubscribed: <ScrollEvent> {1}", id_);
        object_->template unsubscribe<ScrollEvent>(id_);
      }
    protected:
      virtual bool onScrollEvent(const ScrollEvent& e) { return false; }
    private:
      C* object_;
      UUID id_;
    };

    class FlugelEventSubscriber :
        public AppEventSubscriber,
        public RenderEventSubscriber,
        public LogicEventSubscriber,
        public WindowEventSubscriber,
        public KeyboardEventSubscriber,
        public MouseEventSubscriber,
        public CursorEventSubscriber,
        public ScrollEventSubscriber {
    public:
      explicit FlugelEventSubscriber(C* object)
        : AppEventSubscriber{object},
          RenderEventSubscriber{object},
          LogicEventSubscriber{object},
          WindowEventSubscriber{object},
          KeyboardEventSubscriber{object},
          MouseEventSubscriber{object},
          CursorEventSubscriber{object},
          ScrollEventSubscriber{object} {}
    };

    template<typename Event_t>
    UUID subscribe(typename Notifier<Event_t>::EventFn eventFn) {
      FF_ASSERT_E(false, "Unknown event type!");
      return {};
    }
    template<>
    UUID subscribe<AppEvent>(Notifier<AppEvent>::EventFn eventFn) {
      return appNotifier_.subscribe(std::move(eventFn));
    }
    template<>
    UUID subscribe<RenderEvent>(Notifier<RenderEvent>::EventFn eventFn) {
      return renderNotifier_.subscribe(std::move(eventFn));
    }
    template<>
    UUID subscribe<LogicEvent>(Notifier<LogicEvent>::EventFn eventFn) {
      return logicNotifier_.subscribe(std::move(eventFn));
    }
    template<>
    UUID subscribe<WindowEvent>(Notifier<WindowEvent>::EventFn eventFn) {
      return windowNotifier_.subscribe(std::move(eventFn));
    }
    template<>
    UUID subscribe<KeyboardEvent>(Notifier<KeyboardEvent>::EventFn eventFn) {
      return keyNotifier_.subscribe(std::move(eventFn));
    }
    template<>
    UUID subscribe<MouseEvent>(Notifier<MouseEvent>::EventFn eventFn) {
      return mouseNotifier_.subscribe(std::move(eventFn));
    }
    template<>
    UUID subscribe<CursorEvent>(Notifier<CursorEvent>::EventFn eventFn) {
      return cursorNotifier_.subscribe(std::move(eventFn));
    }
    template<>
    UUID subscribe<ScrollEvent>(Notifier<ScrollEvent>::EventFn eventFn) {
      return scrollNotifier_.subscribe(std::move(eventFn));
    }

    template<typename Event_t>
    void unsubscribe(const UUID& id) {
      FF_ASSERT_E(false, "Unknown event type!");
    }
    template<>
    void unsubscribe<AppEvent>(const UUID& id) {
      appNotifier_.unsubscribe(id);
    }
    template<>
    void unsubscribe<RenderEvent>(const UUID& id) {
      renderNotifier_.unsubscribe(id);
    }
    template<>
    void unsubscribe<LogicEvent>(const UUID& id) {
      logicNotifier_.unsubscribe(id);
    }
    template<>
    void unsubscribe<WindowEvent>(const UUID& id) {
      windowNotifier_.unsubscribe(id);
    }
    template<>
    void unsubscribe<KeyboardEvent>(const UUID& id) {
      keyNotifier_.unsubscribe(id);
    }
    template<>
    void unsubscribe<MouseEvent>(const UUID& id) {
      mouseNotifier_.unsubscribe(id);
    }
    template<>
    void unsubscribe<CursorEvent>(const UUID& id) {
      cursorNotifier_.unsubscribe(id);
    }
    template<>
    void unsubscribe<ScrollEvent>(const UUID& id) {
      scrollNotifier_.unsubscribe(id);
    }

  protected:
    Notifier<AppEvent>      appNotifier_;
    Notifier<RenderEvent>   renderNotifier_;
    Notifier<LogicEvent>    logicNotifier_;
    Notifier<WindowEvent>   windowNotifier_;
    Notifier<KeyboardEvent> keyNotifier_;
    Notifier<MouseEvent>    mouseNotifier_;
    Notifier<CursorEvent>   cursorNotifier_;
    Notifier<ScrollEvent>   scrollNotifier_;
  };
}

