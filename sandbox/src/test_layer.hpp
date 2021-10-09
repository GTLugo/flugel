#pragma once

#include "flugel.hpp"

namespace Sandbox {
  class TestLayer : public fge::Layer {
  public:
    TestLayer(const fge::Time& time)
      : Layer{"test_layer"}, time_{time} {}

    virtual void updateFixed() override {
      //FLUGEL_TRACE("UwU");
    }

    virtual void update() override {
      if (fge::Input::isPressed(fge::Key::Space)) {
        FGE_TRACE("OwO");
      }
      //FLUGEL_TRACE("UwU");
    }
  private:
    const fge::Time& time_;
  };
}