#pragma once

namespace fge {
  class Key {
  public:
    enum State : int32_t {
      Released,
      Pressed,
      Repeat
    };

    /// TODO: mark these with unicode values for printing as char
    enum Code : int32_t {
      Unknown = -1,
      _1, _2, _3, _4, _5, _6, _7, _8, _9, _0, // num row
      Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9, Num0, // numpad numbers
      F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, // f-row part 1
      F11, F12, F13, F14, F15, F16, F17, F18, F19, F20, // f-row electric boogaloo
      F21, F22, F23, F24, F25, // f-row part 3
      A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, // letters
      Space, Tab, Enter, NumEnter, // whitespace
      Semicolon, Period, Comma, Apostrophe, // punctuation
      Minus, Equal, ForwardSlash, BackSlash, // math
      LeftBracket, RightBracket, // brackets
      Escape, Menu, Pause, Backspace, Insert, Delete, PrintScreen, // non-visible
      CapsLock, ScrollLock, NumLock, // locks
      Up, Down, Left, Right, PageUp, PageDown, Home, End, // direction
      NumPeriod, NumPlus, NumHyphen, NumSlash, NumAsterisk, NumEqual, // numpad math
      LeftShift, LeftControl, LeftAlt, LeftSuper, // left modifiers
      RightShift, RightControl, RightAlt, RightSuper, // right modifiers
      World1, World2, // international
    };

    static int32_t toNative(Code key) { 
      return keyMap_.at(key);
    }

    static Code fromNative(int32_t key) {
      for (const auto& itr : keyMap_) {
        if (itr.second == key) {
          return itr.first;
        }
      } 
      return Unknown;
    };

    static std::string toString(Code keyCode) {
      return nameMap_.at(keyCode);
    }
  protected:
    static std::map<Code, int32_t> keyMap_;
    static std::map<Code, std::string> nameMap_;
  };
  
  class Modifier {
  public:
    using BitCodes = int32_t;

    enum Code : int32_t {
      None     = 0,
      Shift    = BIT(0),
      Control  = BIT(1),
      Alt      = BIT(2),
      Super    = BIT(3),
      CapsLock = BIT(4),
      NumLock  = BIT(5),
    };


    static int32_t toNative(Code mod) { 
      return modMap_.at(mod); 
    }

    static int32_t toNativeBits(BitCodes mods) {
      int32_t result{0};
      if (mods & Shift)    result |= toNative(Shift);
      if (mods & Control)  result |= toNative(Control);
      if (mods & Alt)      result |= toNative(Alt);
      if (mods & Super)    result |= toNative(Super);
      if (mods & CapsLock) result |= toNative(CapsLock);
      if (mods & NumLock)  result |= toNative(NumLock);
      return result;
    }

    static Code fromNative(int32_t mod) {
      int32_t modifiers{0};
      for (const auto& itr : modMap_) {
        if (itr.second == mod) {
          return itr.first;
        }
      }
      return None;
    };

    static BitCodes fromNativeBits(int32_t mods) {
      BitCodes result{0};
      if (mods & toNative(Shift))    result |= Shift;
      if (mods & toNative(Control))  result |= Control;
      if (mods & toNative(Alt))      result |= Alt;
      if (mods & toNative(Super))    result |= Super;
      if (mods & toNative(CapsLock)) result |= CapsLock;
      if (mods & toNative(NumLock))  result |= NumLock;
      return result;
    }
  protected:
    static std::map<Code, int32_t> modMap_;
  };
}