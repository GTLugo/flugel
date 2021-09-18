#pragma once

#include "event.hpp"

namespace Flugel {
  class FLUGEL_API MouseMovedEvent : public Event {
  public:
    MouseMovedEvent(float x, float y)
      : mouseX_{x}, mouseY_{y} {}
    
    inline float getX() const { return mouseX_; }
    inline float getY() const { return mouseY_; }
    
    std::string toString() const override {
      std::stringstream ss;
      ss << "EVENT <" << getName() << "> (" << mouseX_ << ", " << mouseY_ << ")";
      return ss.str();
    }
    
    EVENT_CLASS_TYPE(MouseMoved)
    EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
  private:
    float mouseX_, mouseY_;
  };

  class FLUGEL_API MouseScrolledEvent : public Event {
  public:
    MouseScrolledEvent(float xOffset, float yOffset)
      : mouseXOffset_{xOffset}, mouseYOffset_{yOffset} {}
    
    inline float getXOffset() const { return mouseXOffset_; }
    inline float getYOffset() const { return mouseYOffset_; }
    
    std::string toString() const override {
      std::stringstream ss;
      ss << "EVENT <" << getName() << "> (" << mouseXOffset_ << ", " << mouseYOffset_ << ")";
      return ss.str();
    }
    
    EVENT_CLASS_TYPE(MouseScrolled)
    EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
  private:
    float mouseXOffset_, mouseYOffset_;
  };

  class FLUGEL_API MouseButtonEvent : public Event {
  public:
    
    inline float getMouseButton() const { return button_; }
    
    EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
  protected:
    MouseButtonEvent(int button)
      : button_{button} {}

    int button_;
  };

  class FLUGEL_API MouseButtonPressedEvent : public MouseButtonEvent {
  public:
    MouseButtonPressedEvent(int button)
      : MouseButtonEvent{button} {}
    
    std::string toString() const override {
      std::stringstream ss;
      ss << "EVENT <" << getName() << "> (" << getMouseButton() << ")";
      return ss.str();
    }
    
    EVENT_CLASS_TYPE(MousePressed)
  };

  class FLUGEL_API MouseButtonReleasedEvent : public MouseButtonEvent {
  public:
    MouseButtonReleasedEvent(int button)
      : MouseButtonEvent{button} {}
    
    std::string toString() const override {
      std::stringstream ss;
      ss << "EVENT <" << getName() << "> (" << getMouseButton() << ")";
      return ss.str();
    }
    
    EVENT_CLASS_TYPE(MouseReleased)
  };
}