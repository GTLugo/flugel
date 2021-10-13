#pragma once

#include "flugel.hpp"

namespace sbx {
  class TestLayer : public fge::Layer {
  public:
    TestLayer()
      : Layer{"test_layer"} {}

    virtual void onUpdateFixedEvent(fge::AppUpdateFixedEvent& e) override {
      if (fge::Input::isPressed(fge::Key::Space) && !fge::Input::isPressed(fge::Key::LeftShift)) {
        FGE_TRACE("UwU");
      }
      if (fge::Input::isPressed(fge::Key::Space) && fge::Input::isPressed(fge::Key::LeftShift)) {
        FGE_TRACE("OwO");
      }
    }

    virtual void onUpdateEvent(fge::AppUpdateEvent& e) override {
      //FGE_TRACE("UwU");
    }

    virtual bool onMouseEvent(fge::MouseEvent& e) override {
      FGE_DEBUG("{}: {}", name_, e);
      return true;
    }

    virtual bool onKeyboardEvent(fge::KeyboardEvent& e) override {
      FGE_DEBUG("{}: {}", name_, e);
      return true;
    }
  };
}