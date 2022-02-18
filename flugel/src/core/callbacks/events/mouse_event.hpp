#pragma once

#include "event.hpp"
#include "core/input/input.hpp"

namespace fge {
  class FGE_API MouseEvent : public Event {
  public:
    EVENT_TYPE(Event::Type::Mouse)

    MouseEvent(Mouse::State buttonState, Mouse::Code button, Modifier::BitCodes mods)
      : buttonState_{buttonState}, button_{button}, mods_{mods} {}

    /// TODO: Move button state to input enum. Add Repeat state for key
    Mouse::State buttonState() const { return buttonState_; }
    Mouse::Code button() const { return button_; }
    Modifier::BitCodes mods() const { return mods_; }
    
    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <Mouse> (" << buttonState_ << ": " << Mouse::toString(button_) << " + " << mods_ << ")";
      return ss.str();
    }
  protected:
    Mouse::State buttonState_;
    Mouse::Code button_;
    Modifier::BitCodes mods_;
  };

  class FGE_API CursorEvent : public Event {
  public:
    EVENT_TYPE(Event::Type::Cursor)

    CursorEvent(double xPos, double yPos)
      : xPos_{xPos}, yPos_{yPos} {}

    double xPos() const { return xPos_; }
    double yPos() const { return yPos_; }
    
    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <Cursor> (" << xPos_ << ", " << yPos_ << ")";
      return ss.str();
    }
  protected:
    double xPos_, yPos_;
  };

  class FGE_API ScrollEvent : public Event {
  public:
    EVENT_TYPE(Event::Type::Scroll)

    ScrollEvent(double xOffset, double yOffset)
      : xOffset_{xOffset}, yOffset_{yOffset} {}

    double xOffset() const { return xOffset_; }
    double yOffset() const { return yOffset_; }
    
    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <Scroll> (" << xOffset_ << ", " << yOffset_ << ")";
      return ss.str();
    }
  protected:
    const double xOffset_, yOffset_;
  };
}