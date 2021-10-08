#pragma once

#include "flugel.hpp"

namespace Sandbox {
  class SandboxLayer : public Flugel::Layer {
  public:
    SandboxLayer(const Flugel::Time* time)
      : Layer{"Sandbox Layer"}, time_{time} {}

    void updateFixed() override {
      //FLUGEL_TRACE("UwU");
    }
    
    bool onKeyboardEvent(Flugel::KeyboardEvent& e) override {
      //FLUGEL_DEBUG("{0}: {1}", name_, e);
      return true;
    }
  private:
    const Flugel::Time* time_;
  };
}