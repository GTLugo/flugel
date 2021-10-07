#pragma once

#include "event.hpp"

namespace Flugel {
  class FLUGEL_API MouseEvent : public Event {
  public:
    EVENT_CATEGORY(Mouse)

    MouseEvent(ButtonState buttonState, int32_t button)
      : buttonState_{buttonState}, button_{button} {}

    ButtonState buttonState() const { return buttonState_; }
    int32_t button() const { return button_; }
    
    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <Mouse> (" << button_ << ", " << buttonState_ << ")";
      return ss.str();
    }
  protected:
    ButtonState buttonState_;
    int32_t button_;
  };

  class FLUGEL_API CursorEvent : public Event {
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

  class FLUGEL_API ScrollEvent : public Event {
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
    double xOffset_, yOffset_;
  };
}