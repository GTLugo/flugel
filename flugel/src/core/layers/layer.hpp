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

    inline virtual void updateFixed() {}
    inline virtual void update() {}
    inline virtual void render() {}
    
    void onEvent(Event& e) {
      EventDispatcher dispatcher{e};
      //FGE_DEBUG_ENG("{0}: {1}", name_, e);
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

    virtual bool onAppEvent(AppEvent& e);
    virtual bool onWindowEvent(WindowEvent& e);
    virtual bool onKeyboardEvent(KeyboardEvent& e);
    virtual bool onMouseEvent(MouseEvent& e);
    virtual bool onCursorEvent(CursorEvent& e);
    virtual bool onScrollEvent(ScrollEvent& e);
  };
}