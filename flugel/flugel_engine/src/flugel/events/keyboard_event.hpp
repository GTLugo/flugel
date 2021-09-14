#pragma once

#include "event.hpp"

#include <sstream>

namespace Flugel {
  class FLUGEL_API KeyboardEvent : public Event {
  public:
    inline int getKeyCode() const { return keyCode_; }

    EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard)
  protected:
    KeyboardEvent(int keyCode)
      : keyCode_{keyCode} {}

    int keyCode_;
  };

  class FLUGEL_API KeyPressedEvent : public KeyboardEvent {
  public:
    KeyPressedEvent(int keyCode, int repeatCount)
      : KeyboardEvent{keyCode}, repeatCount_{repeatCount} {}
    
    inline int getRepeatCount() const { return repeatCount_; }
    std::string toString() const override {
      std::stringstream ss;
      ss << "EVENT <KeyPressed> (" << keyCode_ << ", " << repeatCount_ << "repeats)";
      return ss.str();
    }

    EVENT_CLASS_TYPE(KeyPressed)
  private:
    int repeatCount_;
  };

  class FLUGEL_API KeyReleasedEvent : public KeyboardEvent {
  public:
    KeyReleasedEvent(int keyCode, int repeatCount)
      : KeyboardEvent{keyCode} {}
    
    std::string toString() const override {
      std::stringstream ss;
      ss << "EVENT <KeyPressed> (" << keyCode_ << ")";
      return ss.str();
    }

    EVENT_CLASS_TYPE(KeyReleased)
  };
}