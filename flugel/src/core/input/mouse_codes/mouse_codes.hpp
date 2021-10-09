#pragma once

namespace fge {
  
  class Mouse {
  public:
    enum Code : int32_t {
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

    virtual ~Mouse() { FGE_TRACE_ENG("Destructing Mouse..."); }
    static int32_t toNative(Code button) { return instance_->nativeButtonImpl(button); }
    static Code fromNative(int32_t button) { return instance_->fromNativeImpl(button); }
  protected:
    virtual int32_t nativeButtonImpl(Code button) = 0;
    virtual Code fromNativeImpl(int32_t button) = 0;
  private:
    static Unique<Mouse> instance_;
  };
}