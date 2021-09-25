#pragma once

// REIMPLEMENTATION OF EVENT SYSTEM BY TheCherno

namespace Flugel {
  enum class EventType {
    None = 0,
    WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
    AppStart, AppTick, AppUpdate, AppRender, AppEnd,
    KeyPressed, KeyReleased,
    MousePressed, MouseReleased, MouseMoved, MouseScrolled,
  };

  enum EventCategory {
    None = 0,
    EventCategoryApp           = BIT(0),
    EventCategoryInput         = BIT(1),
    EventCategoryKeyboard      = BIT(2),
    EventCategoryMouse         = BIT(3),
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

  inline std::ostream& operator<<(std::ostream& out, const Event& e) {
    return out << e.toString();
  }

  class EventDispatcher {
    /*
     * EventFn's will be implemented elsewhere (such as in the class handling the event)
     *
     * The function should take in an event type (WindowClose, MouseButtonPressed, etc)
     * and return a bool
    */
    template<typename T>
    using EventFn = std::function<bool(T&)>;
  public:
    EventDispatcher(Event& event)
      : event_{event} {}

    template<typename T>
    bool dispatch(EventFn<T> eventFunc) {
      if (event_.getEventType() == T::getStaticType()) {
        event_.handled_ = eventFunc(*(T*)&event_);
        return true;
      }
      return false;
    }
  private:
    Event& event_;
  };
}