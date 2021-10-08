#pragma once

#include "event.hpp"

namespace Flugel {
  enum class WindowEventType {
    None = 0,
    Close, Resize, Focus, LostFocus, Moved,
  };

  class FLUGEL_API WindowEvent : public Event {
  public:
    EVENT_CATEGORY(Window)

    WindowEventType type() const { return type_; }
  protected:
    const WindowEventType type_;

    WindowEvent(WindowEventType type)
      : type_{type} {}
  };

  class FLUGEL_API WindowCloseEvent : public WindowEvent {
  public:
    WindowCloseEvent()
     : WindowEvent{WindowEventType::Close} {}

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <Window> (CLOSE)";
      return ss.str();
    }
  };

  class FLUGEL_API WindowResizeEvent : public WindowEvent {
  public:
    WindowResizeEvent(uint32_t width, uint32_t height)
      : WindowEvent{WindowEventType::Resize}, width_{width}, height_{height} {}

    uint32_t width() const { return width_; }
    uint32_t height() const { return height_; }

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <Window> (RESIZE: " << width_ << ", " << height_ << ")";
      return ss.str();
    }
  private:
    const uint32_t width_, height_;
  };

  class FLUGEL_API WindowMovedEvent : public WindowEvent {
  public:
    WindowMovedEvent(int32_t xPos, int32_t yPos)
      : WindowEvent{WindowEventType::Resize}, xPos_{xPos}, yPos_{yPos} {}

    uint32_t xPos() const { return xPos_; }
    uint32_t yPos() const { return yPos_; }

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <Window> (MOVED: " << xPos_ << ", " << yPos_ << ")";
      return ss.str();
    }
  private:
    const int32_t xPos_, yPos_;
  };
}