#pragma once

// BASED HEAVILY ON TheCherno's IMPLEMENTATION IN HIS GAME ENGINE SERIES
// https://thecherno.com/engine

namespace fge {

  #define EVENT_CATEGORY(event_cat) static Category categoryStatic() { return event_cat; }\
                                   virtual Category category() const override { return categoryStatic(); }
  
  class FGE_API Event {
    friend class EventDispatcher;
  public:
    enum Category {
      None     = 0b0,
      App      = 0b1,
      Render   = 0b10,
      Logic    = 0b100,
      Window   = 0b1000,
      Keyboard = 0b10000,
      Mouse    = 0b100000,
      Cursor   = 0b1000000,
      Scroll   = 0b10000000,

      Input    = Keyboard | Cursor | Mouse | Scroll,
    };

    [[nodiscard]] virtual Category category() const = 0;
    [[nodiscard]] virtual std::string toString() const = 0;
    [[nodiscard]] virtual bool wasHandled() const { return wasHandled_; }
  protected:
    bool wasHandled_{false};
  };

  inline std::ostream& operator<<(std::ostream& out, const Event& e) {
    return out << e.toString();
  }

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