#pragma once

#include "core/callbacks/events/event.hpp"
#include "core/callbacks/events/app_event.hpp"
#include "core/callbacks/events/window_event.hpp"
#include "core/callbacks/events/keyboard_event.hpp"
#include "core/callbacks/events/mouse_event.hpp"

namespace fge {
  class FGE_API Layer {
  public:
    Layer(const std::string& name = "layer");
    virtual ~Layer();
    
    virtual void attach() {}
    virtual void detach() {}
    
    void onEvent(Event& e) {
      EventDispatcher d{e};
      //FGE_DEBUG_ENG("{0}: {1}", name_, e);
      switch (e.category()) {
        case EventCategory::App:      { return d.dispatch<AppEvent>     (FGE_BIND(onAppEvent));      }
        case EventCategory::Window:   { return d.dispatch<WindowEvent>  (FGE_BIND(onWindowEvent));   }
        case EventCategory::Keyboard: { return d.dispatch<KeyboardEvent>(FGE_BIND(onKeyboardEvent)); }
        case EventCategory::Mouse:    { return d.dispatch<MouseEvent>   (FGE_BIND(onMouseEvent));    }
        case EventCategory::Cursor:   { return d.dispatch<CursorEvent>  (FGE_BIND(onCursorEvent));   }
        case EventCategory::Scroll:   { return d.dispatch<ScrollEvent>  (FGE_BIND(onScrollEvent));   }
      }
    }

    const std::string& name() const { return name_; }
  protected:
    std::string name_;
    // bool enabled_;

    virtual bool onAppEvent(AppEvent& e);

    // virtual bool onStartEvent(AppStartEvent& e)               { return false; }
    // virtual bool onMainStartEvent(AppMainStartEvent& e)       { return false; }
    // virtual bool onRenderStartEvent(AppRenderStartEvent& e)   { return false; }

    // virtual bool onPollEvent(AppPollEvent& e)                 { return false; }
    // virtual bool onFixedUpdateEvent(AppFixedUpdateEvent& e)   { return false; }
    // virtual bool onUpdateEvent(AppUpdateEvent& e)             { return false; }
    // virtual bool onMainUpdateEvent(AppMainUpdateEvent& e)     { return false; }
    // virtual bool onRenderUpdateEvent(AppRenderUpdateEvent& e) { return false; }

    // virtual bool onEndEvent(AppEndEvent& e)                   { return false; }
    // virtual bool onMainEndEvent(AppMainEndEvent& e)           { return false; }
    // virtual bool onRenderEndEvent(AppRenderEndEvent& e)       { return false; }

    virtual bool onWindowEvent(WindowEvent& e)                { return false; }
    virtual bool onKeyboardEvent(KeyboardEvent& e)            { return false; }
    virtual bool onMouseEvent(MouseEvent& e)                  { return false; }
    virtual bool onCursorEvent(CursorEvent& e)                { return false; }
    virtual bool onScrollEvent(ScrollEvent& e)                { return false; }
  private:
    // virtual bool onAppEvent(AppEvent& e);
  };
}