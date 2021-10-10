#pragma once

namespace fge {
  class Mouse {
  public:
    enum State : int32_t {
      Released,
      Pressed
    };

    enum Code : int32_t {
      Unknown = 0,
      _1,
      _2,
      _3,
      _4,
      _5,
      _6,
      _7,
      _8,
      
      Left = _1,
      Right = _2,
      Middle = _3,
      Back = _4,
      Forward = _5,
    };
    
    static int32_t toNative(Code button);
    static Code fromNative(int32_t button);
  protected:
    static std::map<Code, int32_t> mouseMap_;
  };
}