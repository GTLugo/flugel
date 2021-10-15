#pragma once

#include "flugel.hpp"

namespace sbx {
  class TestLayer : public fge::Layer {
  public:
    TestLayer()
      : Layer{"test_layer"} {}

    virtual bool onAppEvent(fge::AppEvent& e) override {
      switch (e.type()) {
        case fge::AppEventType::FixedUpdate: {
          if (fge::Input::isPressed(fge::Key::Space) && !fge::Input::isPressed(fge::Key::LeftShift)) {
            FGE_TRACE("UwU");
          }
          if (fge::Input::isPressed(fge::Key::Space) && fge::Input::isPressed(fge::Key::LeftShift)) {
            FGE_TRACE("OwO");
          }
          return false;
        }
        default: {
          return false;
        }
      }
    }

    virtual bool onMouseEvent(fge::MouseEvent& e) override {
      //FGE_DEBUG("{}: {}", name_, e);
      return true;
    }

    virtual bool onKeyboardEvent(fge::KeyboardEvent& e) override {
      //FGE_DEBUG("{}: {}", name_, e);
      return true;
    }
  };
}