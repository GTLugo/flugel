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
      //FLUGEL_TRACE("UwU");
    }

    virtual bool onKeyboardEvent(fge::KeyboardEvent& e) override {
      FGE_DEBUG("{0}: {1}", name_, e);
      return true;
    }
  private:
    const fge::Time& time_;
  };
}