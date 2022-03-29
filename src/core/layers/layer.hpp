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
  template<class T, class U>
  concept Derived = std::is_base_of<U, T>::value;

  class Layer {
  public:
    class AppEventSubscriber {
    public:
      explicit AppEventSubscriber(Layer* layer) : layer_{layer}, id_{layer->subscribe<AppEvent>(FF_LAMBDA(onAppEvent))}{
        Log::debug_e("Subscribed: <AppEvent> {1}", id_);
      }
      ~AppEventSubscriber() {
        Log::debug_e("Unsubscribed: <AppEvent> {1}", id_);
        layer_->unsubscribe<AppEvent>(id_);
      }
    protected:
      virtual bool onAppEvent(const AppEvent& e) { return false; }
    private:
      Layer* layer_;
      UUID id_;
    };

    class RenderEventSubscriber {
    public:
      explicit RenderEventSubscriber(Layer* layer) : layer_{layer}, id_{layer->subscribe<RenderEvent>(FF_LAMBDA(onRenderEvent))} {
        Log::debug_e("Subscribed: <RenderEvent> {1}", id_);
      }
      ~RenderEventSubscriber() {
        Log::debug_e("Unsubscribed: <RenderEvent> {1}", id_);
        layer_->unsubscribe<RenderEvent>(id_);
      }
    protected:
      virtual bool onRenderEvent(const RenderEvent& e) { return false; }
    private:
      Layer* layer_;
      UUID id_;
    };

    class LogicEventSubscriber {
    public:
      explicit LogicEventSubscriber(Layer* layer) : layer_{layer}, id_{layer->subscribe<LogicEvent>(FF_LAMBDA(onLogicEvent))} {
        Log::debug_e("Subscribed: <LogicEvent> {1}", id_);
      }
      ~LogicEventSubscriber() {
        Log::debug_e("Unsubscribed: <LogicEvent> {1}", id_);
        layer_->unsubscribe<LogicEvent>(id_);
      }
    protected:
      virtual bool onLogicEvent(const LogicEvent& e) { return false; }
    private:
      Layer* layer_;
      UUID id_;
    };

    class WindowEventSubscriber {
    public:
      explicit WindowEventSubscriber(Layer* layer) : layer_{layer}, id_{layer->subscribe<WindowEvent>(FF_LAMBDA(onWindowEvent))} {
        Log::debug_e("Subscribed: <WindowEvent> {1}", id_);
      }
      ~WindowEventSubscriber() {
        Log::debug_e("Unsubscribed: <WindowEvent> {1}", id_);
        layer_->unsubscribe<WindowEvent>(id_);
      }
    protected:
      virtual bool onWindowEvent(const WindowEvent& e) { return false; }
    private:
      Layer* layer_;
      UUID id_;
    };

    class KeyboardEventSubscriber {
    public:
      explicit KeyboardEventSubscriber(Layer* layer) : layer_{layer}, id_{layer->subscribe<KeyboardEvent>(FF_LAMBDA(onKeyboardEvent))} {
        Log::debug_e("Subscribed: <KeyboardEvent> {1}", id_);
      }
      ~KeyboardEventSubscriber() {
        Log::debug_e("Unsubscribed: <KeyboardEvent> {1}", id_);
        layer_->unsubscribe<KeyboardEvent>(id_);
      }
    protected:
      virtual bool onKeyboardEvent(const KeyboardEvent& e) { return false; }
    private:
      Layer* layer_;
      UUID id_;
    };

    class MouseEventSubscriber {
    public:
      explicit MouseEventSubscriber(Layer* layer) : layer_{layer}, id_{layer->subscribe<MouseEvent>(FF_LAMBDA(onMouseEvent))} {
        Log::debug_e("Subscribed: <MouseEvent> {1}", id_);
      }
      ~MouseEventSubscriber() {
        Log::debug_e("Unsubscribed: <MouseEvent> {1}", id_);
        layer_->unsubscribe<MouseEvent>(id_);
      }
    protected:
      virtual bool onMouseEvent(const MouseEvent& e) { return false; }
    private:
      Layer* layer_;
      UUID id_;
    };

    class CursorEventSubscriber {
    public:
      explicit CursorEventSubscriber(Layer* layer) : layer_{layer}, id_{layer->subscribe<CursorEvent>(FF_LAMBDA(onCursorEvent))} {
        Log::debug_e("Subscribed: <CursorEvent> {1}", id_);
      }
      ~CursorEventSubscriber() {
        Log::debug_e("Unsubscribed: <CursorEvent> {1}", id_);
        layer_->unsubscribe<CursorEvent>(id_);
      }
    protected:
      virtual bool onCursorEvent(const CursorEvent& e) { return false; }
    private:
      Layer* layer_;
      UUID id_;
    };

    class ScrollEventSubscriber {
    public:
      explicit ScrollEventSubscriber(Layer* layer) : layer_{layer}, id_{layer->subscribe<ScrollEvent>(FF_LAMBDA(onScrollEvent))} {
        Log::debug_e("Subscribed: <ScrollEvent> {1}", id_);
      }
      ~ScrollEventSubscriber() {
        Log::debug_e("Unsubscribed: <ScrollEvent> {1}", id_);
        layer_->unsubscribe<ScrollEvent>(id_);
      }
    protected:
      virtual bool onScrollEvent(const ScrollEvent& e) { return false; }
    private:
      Layer* layer_;
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
        public ScrollEventSubscriber {};

    explicit Layer(std::string name = "layer");
    virtual ~Layer();
    
    virtual void attach() {}
    virtual void detach() {}

    void toggle(bool enabled) { enabled_ = enabled; }
    [[nodiscard]] bool isEnabled() const { return enabled_; }

    [[nodiscard]] const std::string& name() const { return name_; }
    
    void onEvent(const Event& e) {
      if (!enabled_) return;
      switch (e.type()) {
        case Event::App:      { return e.tryHandleAs<AppEvent>     (FF_LAMBDA(onAppEvent_eng));      }
        case Event::Render:   { return e.tryHandleAs<RenderEvent>  (FF_LAMBDA(onRenderEvent_eng));   }
        case Event::Logic:    { return e.tryHandleAs<LogicEvent>   (FF_LAMBDA(onLogicEvent_eng));    }
        case Event::Window:   { return e.tryHandleAs<WindowEvent>  (FF_LAMBDA(onWindowEvent_eng));   }
        case Event::Keyboard: { return e.tryHandleAs<KeyboardEvent>(FF_LAMBDA(onKeyboardEvent_eng)); }
        case Event::Mouse:    { return e.tryHandleAs<MouseEvent>   (FF_LAMBDA(onMouseEvent_eng));    }
        case Event::Cursor:   { return e.tryHandleAs<CursorEvent>  (FF_LAMBDA(onCursorEvent_eng));   }
        case Event::Scroll:   { return e.tryHandleAs<ScrollEvent>  (FF_LAMBDA(onScrollEvent_eng));   }
        default: break;
      }
    }

    template<typename Event_t>
    UUID subscribe(typename Notifier<Event_t>::EventFn eventFn) {
      FF_ASSERT_E(false, "Unknown event type!");
      return {};
    }
    template<>
    UUID subscribe<AppEvent>(Notifier<AppEvent>::EventFn eventFn);
    template<>
    UUID subscribe<RenderEvent>(Notifier<RenderEvent>::EventFn eventFn);
    template<>
    UUID subscribe<LogicEvent>(Notifier<LogicEvent>::EventFn eventFn);
    template<>
    UUID subscribe<WindowEvent>(Notifier<WindowEvent>::EventFn eventFn);
    template<>
    UUID subscribe<KeyboardEvent>(Notifier<KeyboardEvent>::EventFn eventFn);
    template<>
    UUID subscribe<MouseEvent>(Notifier<MouseEvent>::EventFn eventFn);
    template<>
    UUID subscribe<CursorEvent>(Notifier<CursorEvent>::EventFn eventFn);
    template<>
    UUID subscribe<ScrollEvent>(Notifier<ScrollEvent>::EventFn eventFn);

    template<typename Event_t>
    void unsubscribe(const UUID& id) {
      FF_ASSERT_E(false, "Unknown event type!");
    }
    template<>
    void unsubscribe<AppEvent>(const UUID& id);
    template<>
    void unsubscribe<RenderEvent>(const UUID& id);
    template<>
    void unsubscribe<LogicEvent>(const UUID& id);
    template<>
    void unsubscribe<WindowEvent>(const UUID& id);
    template<>
    void unsubscribe<KeyboardEvent>(const UUID& id);
    template<>
    void unsubscribe<MouseEvent>(const UUID& id);
    template<>
    void unsubscribe<CursorEvent>(const UUID& id);
    template<>
    void unsubscribe<ScrollEvent>(const UUID& id);

  protected:
    std::string name_;
    bool enabled_{true};

    Notifier<AppEvent>      appNotifier_;
    Notifier<RenderEvent>   renderNotifier_;
    Notifier<LogicEvent>    logicNotifier_;
    Notifier<WindowEvent>   windowNotifier_;
    Notifier<KeyboardEvent> keyNotifier_;
    Notifier<MouseEvent>    mouseNotifier_;
    Notifier<CursorEvent>   cursorNotifier_;
    Notifier<ScrollEvent>   scrollNotifier_;

    virtual bool onAppEvent(const AppEvent& e) { return false; }
    virtual bool onRenderEvent(const RenderEvent& e) { return false; }
    virtual bool onLogicEvent(const LogicEvent& e) { return false; }
    virtual bool onWindowEvent(const WindowEvent& e) { return false; }
    virtual bool onKeyboardEvent(const KeyboardEvent& e) { return false; }
    virtual bool onMouseEvent(const MouseEvent& e) { return false; }
    virtual bool onCursorEvent(const CursorEvent& e) { return false; }
    virtual bool onScrollEvent(const ScrollEvent& e) { return false; }
  private:
    virtual bool onAppEvent_eng(const AppEvent& e);
    virtual bool onRenderEvent_eng(const RenderEvent& e);
    virtual bool onLogicEvent_eng(const LogicEvent& e);
    virtual bool onWindowEvent_eng(const WindowEvent& e);
    virtual bool onKeyboardEvent_eng(const KeyboardEvent& e);
    virtual bool onMouseEvent_eng(const MouseEvent& e);
    virtual bool onCursorEvent_eng(const CursorEvent& e);
    virtual bool onScrollEvent_eng(const ScrollEvent& e);
  };
}