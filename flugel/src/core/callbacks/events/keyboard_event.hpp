#pragma once

#include "event.hpp"
#include "core/input/input.hpp"

namespace fge {
  class FGE_API KeyboardEvent : public Event {
  public:
    EVENT_TYPE(Event::Type::Keyboard)

    KeyboardEvent(Key::State keyState, Key::Code key, i32 repeatCount, Modifier::BitCodes mods)
      : keyState_{keyState}, key_{key}, repeatCount_{repeatCount}, mods_{mods} {}

    /// TODO: Move button state to input enum. Add Repeat state for key
    [[nodiscard]] Key::State keyState() const { return keyState_; }
    [[nodiscard]] Key::Code key() const { return key_; }
    [[nodiscard]] i32 repeatCount() const { return repeatCount_; }
    [[nodiscard]] Modifier::BitCodes mods() const { return mods_; }
    
    [[nodiscard]] std::string toString() const override {
      std::stringstream ss;
      ss << "Event <Keyboard> (" << keyState_ << ": " << Key::toString(key_) << " + " << mods_ << ", REP: " << repeatCount_ << ")";
      return ss.str();
    }
  protected:
    const Key::State keyState_;
    const Key::Code key_;
    const i32 repeatCount_;
    const Modifier::BitCodes mods_;
  };
}