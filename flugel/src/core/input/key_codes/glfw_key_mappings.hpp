#pragma once

#include "key_codes.hpp"

namespace fge {
  class GlfwKeyMap : public KeyMap {
  protected:
    virtual int32_t nativeKeyImpl(Key key) override { return keyMap_.at(key); }
  private:
    static std::map<Key, int32_t> keyMap_;
  };
}