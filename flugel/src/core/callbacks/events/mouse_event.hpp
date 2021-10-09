#pragma once

#include "event.hpp"
#include "core/input/mouse_codes/mouse_codes.hpp"

namespace fge {
  class FGE_API MouseEvent : public Event {
  public:
    EVENT_CATEGORY(Mouse)

    MouseEvent(ButtonState buttonState, MouseButton button)
      : buttonState_{buttonState}, button_{button} {}

    ButtonState buttonState() const { return buttonState_; }
    MouseButton button() const { return button_; }
    
    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <Mouse> (" << buttonState_ << ": " << static_cast<int32_t>(button_) << ")";
      return ss.str();
    }
  protected:
    ButtonState buttonState_;
    MouseButton button_;
  };

  class FGE_API CursorEvent : public Event {
  public:
    EVENT_CATEGORY(Cursor)

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
    EVENT_CATEGORY(Scroll)

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