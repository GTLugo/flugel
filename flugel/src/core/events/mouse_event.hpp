#pragma once

#include "notifier.hpp"

namespace Flugel {
  class FLUGEL_API MouseButtonEvent : public Event {
  public:
    
    float getMouseButton() const { return button_; }
    
    EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
  protected:
    MouseButtonEvent(int button)
      : button_{button} {}

    int button_;
  };

  class FLUGEL_API MousePressedEvent : public MouseButtonEvent {
  public:
    MousePressedEvent(int button)
      : MouseButtonEvent{button} {}
    
    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <" << getName() << "> (" << getMouseButton() << ")";
      return ss.str();
    }
    
    EVENT_CLASS_TYPE(MousePressed)
  };

  class FLUGEL_API MouseReleasedEvent : public MouseButtonEvent {
  public:
    MouseReleasedEvent(int button)
      : MouseButtonEvent{button} {}
    
    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <" << getName() << "> (" << getMouseButton() << ")";
      return ss.str();
    }
    
    EVENT_CLASS_TYPE(MouseReleased)
  };
  
  class FLUGEL_API MouseMovedEvent : public Event {
  public:
    MouseMovedEvent(double x, double y)
      : xPos_{x}, yPos_{y} {}
    
    double getX() const { return xPos_; }
    double getY() const { return yPos_; }
  
    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <" << getName() << "> (" << xPos_ << ", " << yPos_ << ")";
      return ss.str();
    }
    
    EVENT_CLASS_TYPE(MouseMoved)
    EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
  private:
    double xPos_, yPos_;
  };

  class FLUGEL_API MouseScrolledEvent : public Event {
  public:
    MouseScrolledEvent(double xOffset, double yOffset)
      : xOffset_{xOffset}, yOffset_{yOffset} {}
    
    double getXOffset() const { return xOffset_; }
    double getYOffset() const { return yOffset_; }
    
    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <" << getName() << "> (" << xOffset_ << ", " << yOffset_ << ")";
      return ss.str();
    }
    
    EVENT_CLASS_TYPE(MouseScrolled)
    EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
  private:
    double xOffset_, yOffset_;
  };
}