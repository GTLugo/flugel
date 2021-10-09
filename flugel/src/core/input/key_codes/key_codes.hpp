#pragma once

namespace fge {
  enum class Key {
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

  enum class Modifier {
    None     = 0,
    Shift    = BIT(0),
    Control  = BIT(1),
    Alt      = BIT(2),
    Super    = BIT(3),
    CapsLock = BIT(4),
    NumLock  = BIT(5),
  };
  
  class KeyMap {
  public:
    virtual ~KeyMap() { FGE_TRACE_ENG("Destructing KeyMap..."); }
    static int32_t nativeKey(Key key) { return instance_->nativeKeyImpl(key); }
  protected:
    virtual int32_t nativeKeyImpl(Key key) = 0;
  private:
    static Unique<KeyMap> instance_;
  };
}