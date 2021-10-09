#pragma once

#include "core/input/key_codes/key_codes.hpp"
#include "core/input/mouse_codes/mouse_codes.hpp"

namespace fge {
  class FGE_API Input {
  public:
    virtual ~Input() {
      FGE_TRACE_ENG("Destructing Input...");
    }

    static bool isPressed(Key key) { return instance_->isKeyPressedImpl(key); }
    static bool isPressed(MouseButton button) { return instance_->isMousePressedImpl(button); }
    static vector2_t cursorPos() { return instance_->cursorPosImpl(); }
    static double cursorPosX() { return instance_->cursorPosXImpl(); }
    static double cursorPosY() { return instance_->cursorPosYImpl(); }

  protected:
    virtual bool isKeyPressedImpl(Key key) = 0;
    virtual bool isMousePressedImpl(MouseButton button) = 0;
    virtual vector2_t cursorPosImpl() = 0;
    virtual double cursorPosXImpl() = 0;
    virtual double cursorPosYImpl() = 0;
    
  private:
    static Unique<Input> instance_;
  };
}