#pragma once

#include "core/callbacks/events/event.hpp"
#include "core/callbacks/events/app_event.hpp"
#include "core/callbacks/events/render_event.hpp"
#include "core/callbacks/events/logic_event.hpp"
#include "core/callbacks/events/window_event.hpp"
#include "core/callbacks/events/keyboard_event.hpp"
#include "core/callbacks/events/mouse_event.hpp"

#include "core/callbacks/subscribable.hpp"

namespace ff {
  class Layer : virtual public Subscribable<Layer> {
  public:
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
        case Event::Logic:    { return e.tryHandleAs<LogicEvent>   (FF_LAMBDA(onLogicEvent_eng));    }
        case Event::Render:   { return e.tryHandleAs<RenderEvent>  (FF_LAMBDA(onRenderEvent_eng));   }
        case Event::Window:   { return e.tryHandleAs<WindowEvent>  (FF_LAMBDA(onWindowEvent_eng));   }
        case Event::Keyboard: { return e.tryHandleAs<KeyboardEvent>(FF_LAMBDA(onKeyboardEvent_eng)); }
        case Event::Mouse:    { return e.tryHandleAs<MouseEvent>   (FF_LAMBDA(onMouseEvent_eng));    }
        case Event::Cursor:   { return e.tryHandleAs<CursorEvent>  (FF_LAMBDA(onCursorEvent_eng));   }
        case Event::Scroll:   { return e.tryHandleAs<ScrollEvent>  (FF_LAMBDA(onScrollEvent_eng));   }
        default: break;
      }
    }

  protected:
    std::string name_;
    bool enabled_{true};

    virtual bool onAppEvent(const AppEvent& e) { return false; }
    virtual bool onLogicEvent(const LogicEvent& e) { return false; }
    virtual bool onRenderEvent(const RenderEvent& e) { return false; }
    virtual bool onWindowEvent(const WindowEvent& e) { return false; }
    virtual bool onKeyboardEvent(const KeyboardEvent& e) { return false; }
    virtual bool onMouseEvent(const MouseEvent& e) { return false; }
    virtual bool onCursorEvent(const CursorEvent& e) { return false; }
    virtual bool onScrollEvent(const ScrollEvent& e) { return false; }

  private:
    virtual bool onAppEvent_eng(const AppEvent& e);
    virtual bool onLogicEvent_eng(const LogicEvent& e);
    virtual bool onRenderEvent_eng(const RenderEvent& e);
    virtual bool onWindowEvent_eng(const WindowEvent& e);
    virtual bool onKeyboardEvent_eng(const KeyboardEvent& e);
    virtual bool onMouseEvent_eng(const MouseEvent& e);
    virtual bool onCursorEvent_eng(const CursorEvent& e);
    virtual bool onScrollEvent_eng(const ScrollEvent& e);
  };
}