#pragma once

namespace Flugel {
  class FLUGEL_API Input {
  public:
    virtual ~Input() {
      FLUGEL_TRACE_E("Destructing Input...");
      FLUGEL_TRACE_E("Destructed Input!");
    }

    static bool isKeyPressed(int32_t key) { return instance_->isKeyPressedImpl(key); }
    static bool isMousePressed(int32_t button) { return instance_->isMousePressedImpl(button); }
    static double cursorPosX() { return instance_->cursorPosXImpl(); }
    static double cursorPosY() { return instance_->cursorPosYImpl(); }

  protected:
    virtual bool isKeyPressedImpl(int32_t key) = 0;
    virtual bool isMousePressedImpl(int32_t button) = 0;
    virtual double cursorPosXImpl() = 0;
    virtual double cursorPosYImpl() = 0;
    
  private:
    static Unique<Input> instance_;
  };
}