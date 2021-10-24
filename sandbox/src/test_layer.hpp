#pragma once

#include "flugel.hpp"

namespace sbx {
  class TestLayer : public fge::Layer {
    using Input = fge::Input;
    using Key = fge::Key;
  public:
    TestLayer()
      : Layer{"test_layer"} {}

    virtual bool onLogicEvent(fge::LogicEvent& e) override {
      switch (e.type()) {
        case fge::LogicEventType::Tick: {
          if (Input::isPressed(Key::Space) && !Input::isPressed(Key::LeftShift)) {
            FGE_TRACE("UwU");
          }
          if (Input::isPressed(Key::Space) && Input::isPressed(Key::LeftShift)) {
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