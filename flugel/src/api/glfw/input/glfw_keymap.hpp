#pragma once

#include "core/input/key_codes.hpp"

namespace fge {
  class GlfwKey : public Key {
  protected:
    virtual int32_t nativeKeyImpl(Code key) override { return keyMap_.at(key); }
    virtual Code fromNativeImpl(int32_t key) override {
      for (const auto& itr : keyMap_) {
        if (itr.second == key) {
          return itr.first;
        }
      } 
      return Key::Unknown;
    };
  private:
    static std::map<Code, int32_t> keyMap_;
  };

  class GlfwModifier : public Modifier {
  protected:
    virtual int32_t nativeModImpl(Code mod) override { return modMap_.at(mod); }
    virtual Code fromNativeImpl(int32_t mod) override {
      int32_t modifiers = 0;
      for (const auto& itr : modMap_) {
        if (itr.second == mod) {
          return itr.first;
        }
      }
      return Modifier::None;
    };

    virtual int32_t nativeModsImpl(int32_t mods) {
      int32_t result;
      if (mods & Shift)    result |= nativeModImpl(Shift);
      if (mods & Control)  result |= nativeModImpl(Control);
      if (mods & Alt)      result |= nativeModImpl(Alt);
      if (mods & Super)    result |= nativeModImpl(Super);
      if (mods & CapsLock) result |= nativeModImpl(CapsLock);
      if (mods & NumLock)  result |= nativeModImpl(NumLock);
      return result;
    }

    virtual int32_t fromNativesImpl(int32_t mods) {
      int32_t result;
      if (mods & nativeModImpl(Shift))    result |= Shift;
      if (mods & nativeModImpl(Control))  result |= Control;
      if (mods & nativeModImpl(Alt))      result |= Alt;
      if (mods & nativeModImpl(Super))    result |= Super;
      if (mods & nativeModImpl(CapsLock)) result |= CapsLock;
      if (mods & nativeModImpl(NumLock))  result |= NumLock;
      return result;
    }
  private:
    static std::map<Code, int32_t> modMap_;
  };
}