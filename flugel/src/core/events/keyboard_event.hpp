#pragma once

#include "notifier.hpp"

namespace Flugel {
  class FLUGEL_API KeyboardEvent : public Event {
  public:
    EVENT_CATEGORY(Keyboard)

    KeyboardEvent(ButtonState keyState, int32_t key, int32_t repeatCount, KeyModifiers mods)
      : keyState_{keyState}, key_{key}, repeatCount_{repeatCount}, mods_{mods} {}

    ButtonState keyState() const { return keyState_; }
    int32_t key() const { return key_; }
    int32_t repeatCount() const { return repeatCount_; }
    KeyModifiers mods() const { return mods_; }
    
    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <Keyboard> (" << key_ << " + " << mods_ << ", " << keyState_ << ", " << repeatCount_ << " repeats)";
      return ss.str();
    }
  protected:
    ButtonState keyState_;
    int32_t key_;
    int32_t repeatCount_;
    KeyModifiers mods_;
  };
}