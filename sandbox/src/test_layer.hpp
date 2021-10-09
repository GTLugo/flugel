#pragma once

#include "flugel.hpp"

namespace Sandbox {
  class TestLayer : public Flugel::Layer {
  public:
    TestLayer(const Flugel::Time& time)
      : Layer{"TestLayer"}, time_{time} {}

    void updateFixed() override {
      //FLUGEL_TRACE("UwU");
    }
    
    bool onKeyboardEvent(Flugel::KeyboardEvent& e) override {
      //FLUGEL_DEBUG("{0}: {1}", name_, e);
      return true;
    }
  private:
    const Flugel::Time& time_;
  };
}