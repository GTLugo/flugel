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
    
    static int32_t toNative(Code button);
    static Code fromNative(int32_t button);
  protected:
    static std::map<Code, int32_t> mouseMap_;
  };
}