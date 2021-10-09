#pragma once

// BASED HEAVILY ON TheCherno's IMPLEMENTATION IN HIS GAME ENGINE SERIES
// https://thecherno.com/engine

namespace fge {
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

  /// TODO: Remove this macro! It's unnecesary!
  #define EVENT_CATEGORY(event_cat) static EventCategory categoryStatic() { return event_cat; }\
                                   virtual EventCategory category() const override { return categoryStatic(); }
  
  class FGE_API Event {
    friend class EventDispatcher;
  public:
    virtual EventCategory category() const = 0;
    virtual std::string toString() const = 0;
    virtual bool wasHandled() const { return wasHandled_; }
  protected:
    bool wasHandled_{false};
  };

  inline std::ostream& operator<<(std::ostream& out, const Event& e) {
    return out << e.toString();
  }

  #define FLUGEL_BIND_INPUT_EVENTS(dispatcher) dispatcher.tryDispatch<KeyboardEvent>(FLUGEL_BIND_FN(onKeyboardEvent));\
                                               dispatcher.tryDispatch<MouseEvent>(FGE_BIND(onMouseEvent));\
                                               dispatcher.tryDispatch<CursorEvent>(FGE_BIND(onCursorEvent));\
                                               dispatcher.tryDispatch<ScrollEvent>(FGE_BIND(onScrollEvent))

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
        event_.wasHandled_ = handlerFn(dynamic_cast<Event_t&>(event_));
        return true;
      }
      return false;
    }
  private:
    Event& event_;
  };
}