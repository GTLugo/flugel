#pragma once

namespace fge {
  enum class MouseButton {
    Unknown = 0,
    Left,
    Right,
    Middle,
    Back,
    Forward,
    _6,
    _7,
    _8
  };
  
  class MouseMap {
  public:
    virtual ~MouseMap() { FGE_TRACE_ENG("Destructing KeyMap..."); }
    static int32_t nativeButton(MouseButton button) { return instance_->nativeButtonImpl(button); }
    static MouseButton fromNative(int32_t button) { return instance_->fromNativeImpl(button); }
  protected:
    virtual int32_t nativeButtonImpl(MouseButton button) = 0;
    virtual MouseButton fromNativeImpl(int32_t button) = 0;
  private:
    static Unique<MouseMap> instance_;
  };
}