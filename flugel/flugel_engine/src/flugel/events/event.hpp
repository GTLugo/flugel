#pragma once

// REIMPLEMENTATION OF EVENT SYSTEM BY TheCherno

#include "../core.hpp"

#include <string>
#include <functional>

namespace Flugel {
  enum class EventType {
    None = 0,
    WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
    AppTick, AppUpdate, AppRender,
    KeyPressed, KeyReleased,
    MousePressed, MouseReleased, MouseMoved, MouseScrolled,
  };

  enum EventCategory {
    None = 0,
    EventCategoryApp         = BIT(0),
    EventCategoryInput       = BIT(1),
    EventCategoryKeyboard    = BIT(2),
    EventCategoryMouse       = BIT(3),
    EventCategoryMouseButton = BIT(4),
  };

  #define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return EventType::##type; }\
                                 virtual EventType getEventType() const override { return getStaticType(); }\
                                 virtual const char* getName() const override { return #type; } 
  #define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }

  class FLUGEL_API Event {
    friend class EventDispatcher;
  public:
    virtual EventType getEventType() const = 0;
    virtual const char* getName() const = 0;
    virtual int getCategoryFlags() const = 0;
    virtual std::string toString() const { return getName(); }

    inline bool isInCategory(const EventCategory& category) {
      return getCategoryFlags() & category;
    }
    
  protected:
    bool handled_ = false;
  };

  class EventDispatcher {
    
  };
}