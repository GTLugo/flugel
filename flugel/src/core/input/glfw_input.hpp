#pragma once

#include "input.hpp"

namespace fge {
  class GlfwInput : public Input {
  protected:
    virtual bool isKeyPressedImpl(int32_t key) override;
    virtual bool isMousePressedImpl(int32_t button) override;
    virtual vector2_t cursorPosImpl() override;
    virtual double cursorPosXImpl() override;
    virtual double cursorPosYImpl() override;
  };
}