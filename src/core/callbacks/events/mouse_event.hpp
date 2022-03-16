#pragma once

#include "event.hpp"
#include "core/input/input.hpp"

namespace ff {
  class MouseEvent : public Event {
  public:
    EVENT_TYPE(Event::Type::Mouse)

    MouseEvent(Mouse::State buttonState, Mouse::Code button, Modifier::BitCodes mods)
      : buttonState_{buttonState}, button_{button}, mods_{mods} {}

    /// TODO: Move button state to input enum. Add Repeat state for key
    [[nodiscard]] Mouse::State buttonState() const { return buttonState_; }
    [[nodiscard]] Mouse::Code button() const { return button_; }
    [[nodiscard]] Modifier::BitCodes mods() const { return mods_; }

    template<Mouse::Code B>
    [[nodiscard]] bool check(Mouse::State state) const { return button() == B && buttonState() == state; }

    [[nodiscard]] std::string toString() const override {
      std::stringstream ss;
      ss << "Event <Mouse> (";
      switch (buttonState_) {
        case Mouse::Released:
          ss << "RELEASE";
          break;
        case Mouse::Pressed:
          ss << "PRESS";
          break;
      }
      ss << ": " << Mouse::toString(button_) << " + " << mods_ << ")";
      return ss.str();
    }
  protected:
    Mouse::State buttonState_;
    Mouse::Code button_;
    Modifier::BitCodes mods_;
  };

  class CursorEvent : public Event {
  public:
    EVENT_TYPE(Event::Type::Cursor)

    CursorEvent(double xPos, double yPos)
      : xPos_{xPos}, yPos_{yPos} {}

    [[nodiscard]] double xPos() const { return xPos_; }
    [[nodiscard]] double yPos() const { return yPos_; }
    
    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <Cursor> (" << xPos_ << ", " << yPos_ << ")";
      return ss.str();
    }
  protected:
    double xPos_, yPos_;
  };

  class ScrollEvent : public Event {
  public:
    EVENT_TYPE(Event::Type::Scroll)

    ScrollEvent(double xOffset, double yOffset)
      : xOffset_{xOffset}, yOffset_{yOffset} {}

    [[nodiscard]] double xOffset() const { return xOffset_; }
    [[nodiscard]] double yOffset() const { return yOffset_; }
    
    [[nodiscard]] std::string toString() const override {
      std::stringstream ss;
      ss << "Event <Scroll> (" << xOffset_ << ", " << yOffset_ << ")";
      return ss.str();
    }
  protected:
    const double xOffset_, yOffset_;
  };
}