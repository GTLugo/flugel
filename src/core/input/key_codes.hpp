#pragma once

namespace ff {
  class Key {
  public:
    enum State : i32 {
      Released,
      Pressed,
      Held
    };

    // Based on GLFW
    enum Code : i32 {
      // Printable
      Unknown      = -1,
      Tab          = 9,
      Enter        = 10,
      Space        = 32,
      Apostrophe   = 39, 
      Comma        = 44, 
      Minus        = 45, 
      Period       = 46, 
      ForwardSlash = 47, 
      _0           = 48,
      _1           = 49,
      _2           = 50,
      _3           = 51, 
      _4           = 52, 
      _5           = 53, 
      _6           = 54, 
      _7           = 55, 
      _8           = 56, 
      _9           = 57, 
      Semicolon    = 59,
      Equal        = 61, 
      A            = 65,
      B            = 66, 
      C            = 67, 
      D            = 68, 
      E            = 69, // ;)
      F            = 70, 
      G            = 71, 
      H            = 72, 
      I            = 73, 
      J            = 74, 
      K            = 75, 
      L            = 76, 
      M            = 77, 
      N            = 78, 
      O            = 79, 
      P            = 80, 
      Q            = 81, 
      R            = 82, 
      S            = 83, 
      T            = 84, 
      U            = 85, 
      V            = 86, 
      W            = 87, 
      X            = 88, 
      Y            = 89, 
      Z            = 90,
      LeftBracket  = 91, 
      BackSlash    = 92,
      RightBracket = 93,
      Accent       = 96,
      World1       = 161,
      World2       = 162,
      // Non-printable
      Escape       = 256,
      NumEnter     ,
      Backspace    , 
      Insert       ,
      Delete       ,
      Up           ,
      Down         , 
      Left         , 
      Right        , 
      PageUp       , 
      PageDown     , 
      Home         , 
      End          ,
      CapsLock     ,
      ScrollLock   , 
      NumLock      ,
      PrintScreen  ,
      Pause        , 
      Num0         ,
      Num1         ,
      Num2         , 
      Num3         , 
      Num4         , 
      Num5         , 
      Num6         , 
      Num7         , 
      Num8         , 
      Num9         , 
      F1           ,
      F2           , 
      F3           , 
      F4           , 
      F5           , 
      F6           , 
      F7           , 
      F8           , 
      F9           , 
      F10          ,
      F11          , 
      F12          , 
      F13          , 
      F14          , 
      F15          , 
      F16          , 
      F17          , 
      F18          , 
      F19          , 
      F20          ,
      F21          , 
      F22          , 
      F23          , 
      F24          , 
      F25          , 
      NumPeriod    ,
      NumPlus      , 
      NumHyphen    , 
      NumSlash     , 
      NumAsterisk  , 
      NumEqual     , 
      LeftShift    ,
      LeftControl  , 
      LeftAlt      , 
      LeftSuper    , 
      RightShift   ,
      RightControl , 
      RightAlt     , 
      RightSuper   ,  
      Menu         ,  

      Last         = Menu,
    };

    static i32 toNative(Code key) {
      return keyMap_.at(key);
    }

    static Code fromNative(i32 key) {
      return nativeMap_.at(key);
    };

    static std::string toString(Code keyCode) {
      return nameMap_.at(keyCode);
    }

    static std::string toString(State keyCode) {
      return stateNameMap_.at(keyCode);
    }
  protected:
    static std::map<Code, i32> keyMap_;
    static std::map<i32, Code> nativeMap_;
    static std::map<Code, std::string> nameMap_;
    static std::map<State, std::string> stateNameMap_;
  };
  
  class Modifier {
  public:
    using BitCodes = i32;

    enum Code : i32 {
      None     = 0,
      Shift    = BIT(0),
      Control  = BIT(1),
      Alt      = BIT(2),
      Super    = BIT(3),
      CapsLock = BIT(4),
      NumLock  = BIT(5),
    };


    static i32 toNative(Code mod) {
      return modMap_.at(mod); 
    }

    static i32 toNativeBits(BitCodes mods) {
      i32 result{0};
      if (mods & Shift)    result |= toNative(Shift);
      if (mods & Control)  result |= toNative(Control);
      if (mods & Alt)      result |= toNative(Alt);
      if (mods & Super)    result |= toNative(Super);
      if (mods & CapsLock) result |= toNative(CapsLock);
      if (mods & NumLock)  result |= toNative(NumLock);
      return result;
    }

    static Code fromNative(i32 mod) {
      return nativeMap_.at(mod);
    };

    static BitCodes fromNativeBits(i32 mods) {
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
    static std::map<Code, i32> modMap_;
    static std::map<i32, Code> nativeMap_;
  };
}