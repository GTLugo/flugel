#pragma once

#include "input.hpp"

namespace fge {
  class GlfwInput : public Input {
  protected:
    virtual bool isKeyPressedImpl(Key key) override;
    virtual bool isMousePressedImpl(MouseButton button) override;
    virtual vector2_t cursorPosImpl() override;
    virtual double cursorPosXImpl() override;
    virtual double cursorPosYImpl() override;
  };
}