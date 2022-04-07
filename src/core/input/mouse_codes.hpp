#pragma once

namespace ff {
  class Mouse {
  public:
    enum State : i32 {
      Released,
      Pressed
    };

    enum Code : i32 {
      Unknown = 0,
      _1 = 0x01,
      _2 = 0x02,
      _3 = 0x03,
      _4 = 0x04,
      _5 = 0x05,
      _6 = 0x06,
      _7 = 0x07,
      _8 = 0x08,
      
      Last = _8,
      Left = _1,
      Right = _2,
      Middle = _3,
      Back = _4,
      Forward = _5,
    };

    static i32 toNative(Code button) {
      return mouseMap_.at(button);
    }

    static Code fromNative(i32 button) {
      return nativeMap_.at(button);
    };

    static std::string toString(Code keyCode) {
      return nameMap_.at(keyCode);
    }

    static std::string toString(State keyCode) {
      return stateNameMap_.at(keyCode);
    }
  protected:
    static std::map<Code, i32> mouseMap_;
    static std::map<i32, Code> nativeMap_;
    static std::map<Code, std::string> nameMap_;
    static std::map<State, std::string> stateNameMap_;
  };
}