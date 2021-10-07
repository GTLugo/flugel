#pragma once

// BASED HEAVILY ON TheCherno's IMPLEMENTATION IN HIS GAME ENGINE SERIES
// https://thecherno.com/engine

namespace Flugel {
  enum class EventCategory {
    None = 0,
    App, Window, Keyboard, Mouse, Cursor, Scroll
  };
  
  enum class ButtonState {
    Pressed, Released,
  };

  inline std::ostream& operator<<(std::ostream& out, const ButtonState& b) {
    switch (b) {
      case ButtonState::Pressed: {
        return out << "PRESSED";
      }
      case ButtonState::Released: {
        return out << "RELEASED";
      }
      default: {
        return out << "NULL";
      }
    }
  }

  #define EVENT_CATEGORY(event_cat) static EventCategory categoryStatic() { return EventCategory::##event_cat; }\
                                   virtual EventCategory category() const override { return categoryStatic(); }
  
  class FLUGEL_API Event {
    friend class EventDispatcher;
  public:
    virtual EventCategory category() const = 0;
    virtual std::string toString() const = 0;
  protected:
    bool wasHandled{false};
  };

  inline std::ostream& operator<<(std::ostream& out, const Event& e) {
    return out << e.toString();
  }

  // Takes an event and conditionally dispatches it to a handler if it matches the category type
  class EventDispatcher {
    template<typename Event_t>
    using EventHandlerFn = std::function<bool(Event_t&)>;
  public:
    EventDispatcher(Event& e)
      : event_{e} {}
    
    template<typename Event_t>
    bool tryDispatch(EventHandlerFn<Event_t> handlerFn) {
      if (event_.category() == Event_t::categoryStatic()) {
        event_.wasHandled = handlerFn(dynamic_cast<Event_t&>(event_));
        return true;
      }
      return false;
    }
  private:
    Event& event_;
  };
}