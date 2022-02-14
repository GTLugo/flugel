#pragma once

// BASED HEAVILY ON TheCherno's IMPLEMENTATION IN HIS GAME ENGINE SERIES
// https://thecherno.com/engine

namespace fge {
  enum class EventCategory {
    None = 0,
    App, Render, Logic, Window, Keyboard, Mouse, Cursor, Scroll
  };

  /// TODO: Remove this macro! It's unnecesary!
  #define EVENT_CATEGORY(event_cat) static EventCategory categoryStatic() { return event_cat; }\
                                   virtual EventCategory category() const override { return categoryStatic(); }
  
  class FGE_API Event {
    friend class EventDispatcher;
  public:
    [[nodiscard]] virtual EventCategory category() const = 0;
    [[nodiscard]] virtual std::string toString() const = 0;
    [[nodiscard]] virtual bool wasHandled() const { return wasHandled_; }
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
    explicit EventDispatcher(Event& e)
      : event_{e} {}
    
    template<typename Event_t>
    void dispatch(EventHandlerFn<Event_t> handlerFn) {
      event_.wasHandled_ = handlerFn(dynamic_cast<Event_t&>(event_));
    }
  private:
    Event& event_;
  };
}