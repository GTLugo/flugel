#pragma once

#include "event.hpp"

#include <sstream>

namespace Flugel {
  class FLUGEL_API MouseMovedEvent : public Event {
  public:
    MouseMovedEvent(float x, float y)
      : mouseX_{x}, mouseY_{y} {}
    
    inline float getX() const { return mouseX_; }
    inline float getY() const { return mouseY_; }
    
    std::string toString() const override {
      
    }
    
    EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse | EventCategoryMouseMoved)
  private:
    float mouseX_, mouseY_;
  };
}