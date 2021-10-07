#pragma once

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

  // Courtesy of TheCherno
  #define EVENT_CATEGORY(event_cat) static EventCategory categoryStatic() { return EventCategory::##event_cat; }\
                                   virtual EventCategory category() const override { return categoryStatic(); }
  
  class FLUGEL_API Event {
  public:
    virtual EventCategory category() const = 0;
    virtual std::string toString() const = 0;
  };

  inline std::ostream& operator<<(std::ostream& out, const Event& e) {
    return out << e.toString();
  }
}