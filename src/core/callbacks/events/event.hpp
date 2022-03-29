#pragma once

// BASED HEAVILY ON TheCherno's IMPLEMENTATION IN HIS GAME ENGINE SERIES
// https://thecherno.com/engine

namespace ff {

  #define EVENT_TYPE(event_cat) static Type typeStatic() { return event_cat; }\
                                   virtual Type type() const override { return typeStatic(); }

  
  class Event {
  protected:
    template<typename Event_t>
    using EventHandlerFn = std::function<bool(const Event_t&)>;
  public:
    enum Type {
      None     = 0,
      Window   = BIT(0),
      App      = BIT(1),
      Logic    = BIT(2),
      Render   = BIT(3),
      Keyboard = BIT(4),
      Mouse    = BIT(5),
      Cursor   = BIT(6),
      Scroll   = BIT(7),

      // These might be best to separate out to avoid confusion
      Pipeline = App | Logic | Render,
      Input    = Keyboard | Cursor | Mouse | Scroll,
    };

    [[nodiscard]] virtual Type type() const = 0;
    [[nodiscard]] virtual std::string toString() const = 0;
    [[nodiscard]] virtual bool wasHandled() const { return wasHandled_; }

    template<typename Event_t>
    void tryHandleAs(EventHandlerFn<Event_t> handlerFn) const {
      wasHandled_ = handlerFn(dynamic_cast<const Event_t&>(*this));
    }

  protected:
    mutable bool wasHandled_{false};
  };

  inline std::ostream& operator<<(std::ostream& out, const Event& e) {
    return out << e.toString();
  }
}