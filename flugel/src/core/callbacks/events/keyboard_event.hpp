#pragma once

#include "event.hpp"

namespace Flugel {
  enum KeyModifiers {
    None = 0,
    Shift   = BIT(1),
    Control = BIT(2),
    Alt     = BIT(3),
    Super   = BIT(4),
    Caps    = BIT(5),
    Num     = BIT(6),
  };

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
      ss << "Event <Keyboard> (" << keyState_ << ": " << key_ << " + " << mods_ << ", REP: " << repeatCount_ << ")";
      return ss.str();
    }
  protected:
    const ButtonState keyState_;
    const int32_t key_;
    const int32_t repeatCount_;
    const KeyModifiers mods_;
  };
}