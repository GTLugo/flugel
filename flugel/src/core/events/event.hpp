#pragma once

namespace Flugel {

  enum class EventCategory {
    None = 0,
    App, Window, Keyboard, Mouse, Cursor, Scroll
  };
  
  enum class WindowEventType {
    None = 0,
    Close, Resize, Focus, LostFocus, Moved,
  };
  
  struct WindowEventData {
    uint32_t width, height;
    int32_t xPos, yPos;

    WindowEventData(uint32_t width,
                uint32_t height,
                int32_t xPos,
                int32_t yPos)
      : width{width},
        height{height},
        xPos{xPos},
        yPos{yPos} {}
  };
  
  enum class AppEventType {
    None = 0,
    Start, Tick, UpdateFixed, Update, Render, End,
  };
  
  enum class ButtonState {
    Pressed, Released,
  };
  
  enum KeyModifiers {
    None = 0,
    Shift   = BIT(1),
    Control = BIT(2),
    Alt     = BIT(3),
    Super   = BIT(4),
    Caps    = BIT(5),
    Num     = BIT(6),
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