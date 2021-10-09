#pragma once

#include "input.hpp"

namespace fge {
  class GlfwInput : public Input {
  protected:
    virtual bool isKeyPressedImpl(Key::Code key) override;
    virtual bool isMousePressedImpl(Mouse::Code button) override;
    //virtual bool areModifiersPressedImpl(Modifier::Codes mods) override;
    virtual vector2_t cursorPosImpl() override;
    virtual double cursorPosXImpl() override;
    virtual double cursorPosYImpl() override;
  };
}