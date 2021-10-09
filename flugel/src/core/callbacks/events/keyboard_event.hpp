#pragma once

#include "event.hpp"
#include "core/input/key_codes/key_codes.hpp"

namespace fge {
  class FGE_API KeyboardEvent : public Event {
  public:
    EVENT_CATEGORY(Keyboard)

    KeyboardEvent(ButtonState keyState, Key key, int32_t repeatCount, int32_t mods)
      : keyState_{keyState}, key_{key}, repeatCount_{repeatCount}, mods_{mods} {}

    ButtonState keyState() const { return keyState_; }
    Key key() const { return key_; }
    int32_t repeatCount() const { return repeatCount_; }
    int32_t mods() const { return mods_; }
    
    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <Keyboard> (" << keyState_ << ": " << static_cast<int32_t>(key_) << " + " << mods_ << ", REP: " << repeatCount_ << ")";
      return ss.str();
    }
  protected:
    const ButtonState keyState_;
    const Key key_;
    const int32_t repeatCount_;
    const int32_t mods_;
  };
}