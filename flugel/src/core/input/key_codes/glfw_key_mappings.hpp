#pragma once

#include "key_codes.hpp"

namespace fge {
  class GlfwKeyMap : public KeyMap {
  protected:
    virtual int32_t nativeKeyImpl(Key key) override { return keyMap_.at(key); }
    virtual Key fromNativeImpl(int32_t key) override {
      for (const auto& itr : keyMap_) {
        if (itr.second == key) {
          return itr.first;
        }
      } 
      return Key::Unknown;
    };
  private:
    static std::map<Key, int32_t> keyMap_;
  };

  class GlfwModMap : public ModMap {
  protected:
    virtual int32_t nativeModImpl(KeyMod mod) override { return modMap_.at(mod); }
    virtual KeyMod fromNativeImpl(int32_t mod) override {
      int32_t modifiers = 0;
      for (const auto& itr : modMap_) {
        if (itr.second == mod) {
          return itr.first;
        }
      }
      return KeyMod::None;
    };
  private:
    static std::map<KeyMod, int32_t> modMap_;
  };
}