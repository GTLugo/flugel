#pragma once

namespace fge {

  // inline std::ostream& operator<<(std::ostream& out, const Modifiers& m) {
  //   return out << m.mods_;
  // }
  
  class Key {
  public:
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

    virtual ~Key() { FGE_TRACE_ENG("Destructing Key..."); }
    static int32_t toNative(Code keyCode) { return instance_->nativeKeyImpl(keyCode); }
    static Code fromNative(int32_t keyCode) { return instance_->fromNativeImpl(keyCode); }
  protected:
    virtual int32_t nativeKeyImpl(Code keyCode) = 0;
    virtual Code fromNativeImpl(int32_t keyCode) = 0;
  private:
    static Unique<Key> instance_;
  };
  
  class Modifier {
  public:
    using Codes = int32_t;

    enum Code : int32_t {
      None     = 0,
      Shift    = BIT(0),
      Control  = BIT(1),
      Alt      = BIT(2),
      Super    = BIT(3),
      CapsLock = BIT(4),
      NumLock  = BIT(5),
    };

    virtual ~Modifier() { FGE_TRACE_ENG("Destructing Modifier..."); }
    static int32_t toNative(Code mod) { return instance_->nativeModImpl(mod); }
    static Code fromNative(int32_t mod) { return instance_->fromNativeImpl(mod); }
    
    static int32_t toNatives(int32_t mods) { return instance_->nativeModsImpl(mods); }
    static int32_t fromNatives(int32_t mods) { return instance_->fromNativesImpl(mods); }
  protected:
    virtual int32_t nativeModImpl(Code mod) = 0;
    virtual Code fromNativeImpl(int32_t mod) = 0;

    virtual int32_t nativeModsImpl(Codes mods) = 0;
    virtual Codes fromNativesImpl(int32_t mods) = 0;
  private:
    static Unique<Modifier> instance_;
  };
}