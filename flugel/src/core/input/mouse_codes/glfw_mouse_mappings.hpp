#pragma once

#include "mouse_codes.hpp"

namespace fge {
  class GlfwMouseMap : public MouseMap {
  protected:
    virtual int32_t nativeButtonImpl(MouseButton button) override { return mouseMap_.at(button); }
    virtual MouseButton fromNativeImpl(int32_t button) override {
      for (const auto& itr : mouseMap_) {
        if (itr.second == button) {
          return itr.first;
        }
      } 
      return MouseButton::Unknown;
    };
  private:
    static std::map<MouseButton, int32_t> mouseMap_;
  };
}