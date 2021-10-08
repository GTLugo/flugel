#pragma once

#include "input.hpp"

namespace Flugel {
  class FLUGEL_API GlfwInput : public Input {
  protected:
    virtual bool isKeyPressedImpl(int32_t key) override;
    virtual bool isMousePressedImpl(int32_t button) override;
    virtual double cursorPosXImpl() override;
    virtual double cursorPosYImpl() override;
  };
}