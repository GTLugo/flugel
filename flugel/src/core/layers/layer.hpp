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

    virtual void updateFixed() {}
    virtual void update() {}
    virtual void render() {}
    
    void onEvent(Event& e) {
      EventDispatcher dispatcher{e};
      
      if (dispatcher.tryDispatch<AppEvent>(FGE_BIND(onAppEvent))) return;
      if (dispatcher.tryDispatch<WindowEvent>(FGE_BIND(onWindowEvent))) return;
      if (dispatcher.tryDispatch<KeyboardEvent>(FGE_BIND(onKeyboardEvent))) return;
      if (dispatcher.tryDispatch<MouseEvent>(FGE_BIND(onMouseEvent))) return;
      if (dispatcher.tryDispatch<CursorEvent>(FGE_BIND(onCursorEvent))) return;
      if (dispatcher.tryDispatch<ScrollEvent>(FGE_BIND(onScrollEvent))) return;
    }

    const std::string& name() const { return name_; }
  protected:
    std::string name_;
    // bool enabled_;

    inline virtual bool onAppEvent(AppEvent& e);
    inline virtual bool onWindowEvent(WindowEvent& e);
    inline virtual bool onKeyboardEvent(KeyboardEvent& e);
    inline virtual bool onMouseEvent(MouseEvent& e);
    inline virtual bool onCursorEvent(CursorEvent& e);
    inline virtual bool onScrollEvent(ScrollEvent& e);
  };
}