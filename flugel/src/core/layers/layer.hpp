#pragma once

#include "core/callbacks/events/event.hpp"
#include "core/callbacks/events/app_event.hpp"
#include "core/callbacks/events/render_event.hpp"
#include "core/callbacks/events/logic_event.hpp"
#include "core/callbacks/events/window_event.hpp"
#include "core/callbacks/events/keyboard_event.hpp"
#include "core/callbacks/events/mouse_event.hpp"

namespace fge {
  class FGE_API Layer {
  public:
    explicit Layer(const std::string& name = "layer");
    virtual ~Layer();
    
    virtual void attach() {}
    virtual void detach() {}
    
    void onEvent(Event& e) {
      EventDispatcher d{e};
      //FGE_DEBUG_ENG("{0}: {1}", name_, e);
      switch (e.category()) {
        case EventCategory::App:      { return d.dispatch<AppEvent>     (FGE_BIND(onAppEvent));      }
        case EventCategory::Render:   { return d.dispatch<RenderEvent>  (FGE_BIND(onRenderEvent));   }
        case EventCategory::Logic:    { return d.dispatch<LogicEvent>   (FGE_BIND(onLogicEvent));    }
        case EventCategory::Window:   { return d.dispatch<WindowEvent>  (FGE_BIND(onWindowEvent));   }
        case EventCategory::Keyboard: { return d.dispatch<KeyboardEvent>(FGE_BIND(onKeyboardEvent)); }
        case EventCategory::Mouse:    { return d.dispatch<MouseEvent>   (FGE_BIND(onMouseEvent));    }
        case EventCategory::Cursor:   { return d.dispatch<CursorEvent>  (FGE_BIND(onCursorEvent));   }
        case EventCategory::Scroll:   { return d.dispatch<ScrollEvent>  (FGE_BIND(onScrollEvent));   }
        case EventCategory::None:
          break;
      }
    }

    [[nodiscard]] const std::string& name() const { return name_; }
  protected:
    std::string name_;
    // bool enabled_;

    virtual bool onAppEvent(AppEvent& e)           { return false; }
    virtual bool onRenderEvent(RenderEvent& e)     { return false; }
    virtual bool onLogicEvent(LogicEvent& e)       { return false; }

    virtual bool onWindowEvent(WindowEvent& e)     { return false; }
    virtual bool onKeyboardEvent(KeyboardEvent& e) { return false; }
    virtual bool onMouseEvent(MouseEvent& e)       { return false; }
    virtual bool onCursorEvent(CursorEvent& e)     { return false; }
    virtual bool onScrollEvent(ScrollEvent& e)     { return false; }
  private:
    // virtual bool onAppEvent(AppEvent& e);
  };
}