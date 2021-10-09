#pragma once

#include "core/input/mouse_codes.hpp"

namespace fge {
  class GlfwMouse : public Mouse {
  protected:
    virtual int32_t nativeButtonImpl(Code button) override { return mouseMap_.at(button); }
    virtual Code fromNativeImpl(int32_t button) override {
      for (const auto& itr : mouseMap_) {
        if (itr.second == button) {
          return itr.first;
        }
      } 
      return Mouse::Unknown;
    };
  private:
    static std::map<Code, int32_t> mouseMap_;
  };
}