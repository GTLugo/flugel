#pragma once

#include "flugel.hpp"

namespace Sandbox {
  class TestLayer : public fge::Layer {
  public:
    TestLayer(const fge::Time& time)
      : Layer{"test_layer"}, time_{time} {}

    void updateFixed() override {
      //FLUGEL_TRACE("UwU");
    }
    
    bool onKeyboardEvent(fge::KeyboardEvent& e) override {
      //FLUGEL_DEBUG("{0}: {1}", name_, e);
      return true;
    }
  private:
    const fge::Time& time_;
  };
}