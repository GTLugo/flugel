#pragma once

#include "flugel.hpp"

namespace sbx {
  class TestLayer : public fge::Layer {
  public:
    TestLayer()
      : Layer{"test_layer"} {}

    virtual void onUpdateFixedEvent(fge::AppUpdateFixedEvent& e) override {
      //FLUGEL_TRACE("UwU");
    }

    virtual void onUpdateEvent(fge::AppUpdateEvent& e) override {
      //FLUGEL_TRACE("UwU");
    }

    virtual bool onMouseEvent(fge::MouseEvent& e) override {
      FGE_DEBUG("{0} | {1}: {2}", fge::App::time().deltaTime<fge::Seconds>(), name_, e);
      return true;
    }

    virtual bool onKeyboardEvent(fge::KeyboardEvent& e) override {
      FGE_DEBUG("{0} | {1}: {2}", fge::App::time().deltaTime<fge::Seconds>(), name_, e);
      return true;
    }
  };
}