#pragma once

#include "core/callbacks/events/event.hpp"
#include "core/callbacks/events/app_event.hpp"
#include "core/callbacks/events/window_event.hpp"
#include "core/callbacks/events/keyboard_event.hpp"
#include "core/callbacks/events/mouse_event.hpp"

namespace Flugel {
  class FLUGEL_API Layer {
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

      dispatcher.tryDispatch<WindowEvent>(FLUGEL_BIND_FN(onWindowEvent));
      dispatcher.tryDispatch<KeyboardEvent>(FLUGEL_BIND_FN(onKeyboardEvent));
      dispatcher.tryDispatch<MouseEvent>(FLUGEL_BIND_FN(onMouseEvent));
      dispatcher.tryDispatch<CursorEvent>(FLUGEL_BIND_FN(onCursorEvent));
      dispatcher.tryDispatch<ScrollEvent>(FLUGEL_BIND_FN(onScrollEvent));
    }

    const std::string& name() const { return name_; }
  protected:
    std::string name_;
    // bool enabled_;

    virtual bool onWindowEvent(WindowEvent& e) { return false; }
    virtual bool onKeyboardEvent(KeyboardEvent& e) { return false; }
    virtual bool onMouseEvent(MouseEvent& e) { return false; }
    virtual bool onCursorEvent(CursorEvent& e) { return false; }
    virtual bool onScrollEvent(ScrollEvent& e) { return false; }
  };
}