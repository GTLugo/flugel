#pragma once

#include "event.hpp"
#include "core/input/input.hpp"

namespace fge {
  class FGE_API KeyboardEvent : public Event {
  public:
    EVENT_CATEGORY(Event::Category::Keyboard)

    KeyboardEvent(Key::State keyState, Key::Code key, i32 repeatCount, Modifier::BitCodes mods)
      : keyState_{keyState}, key_{key}, repeatCount_{repeatCount}, mods_{mods} {}

    /// TODO: Move button state to input enum. Add Repeat state for key
    Key::State keyState() const { return keyState_; }
    Key::Code key() const { return key_; }
    i32 repeatCount() const { return repeatCount_; }
    Modifier::BitCodes mods() const { return mods_; }
    
    std::string toString() const override {
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