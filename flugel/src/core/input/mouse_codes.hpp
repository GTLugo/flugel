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

    static int32_t toNative(Code button) { 
      return mouseMap_.at(button);
    }

    static Code fromNative(int32_t button) {
      for (const auto& itr : mouseMap_) {
        if (itr.second == button) {
          return itr.first;
        }
      } 
      return Unknown;
    };

    static std::string toString(Code keyCode) {
      return nameMap_.at(keyCode);
    }
  protected:
    static std::map<Code, int32_t> mouseMap_;
    static std::map<Code, std::string> nameMap_;
  };
}