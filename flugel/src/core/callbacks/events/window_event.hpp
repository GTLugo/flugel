#pragma once

#include "event.hpp"

namespace fge {
  enum class WindowEventType {
    None = 0,
    Close, Resize, Focus, LostFocus, Moved,
  };

  class FGE_API WindowEvent : public Event {
  public:
    EVENT_CATEGORY(EventCategory::Window)

    [[nodiscard]] WindowEventType type() const { return type_; }
  protected:
    const WindowEventType type_;

    explicit WindowEvent(WindowEventType type)
      : type_{type} {}
  };

  class FGE_API WindowCloseEvent : public WindowEvent {
  public:
    WindowCloseEvent()
     : WindowEvent{WindowEventType::Close} {}

    [[nodiscard]] std::string toString() const override {
      std::stringstream ss;
      ss << "Event <Window> (CLOSE)";
      return ss.str();
    }
  };

  class FGE_API WindowResizeEvent : public WindowEvent {
  public:
    WindowResizeEvent(i32 width, i32 height)
      : WindowEvent{WindowEventType::Resize}, width_{width}, height_{height} {}

    [[nodiscard]] i32 width() const { return width_; }
    [[nodiscard]] i32 height() const { return height_; }

    [[nodiscard]] std::string toString() const override {
      std::stringstream ss;
      ss << "Event <Window> (RESIZE: " << width_ << ", " << height_ << ")";
      return ss.str();
    }
  private:
    const i32 width_, height_;
  };

  class FGE_API WindowMovedEvent : public WindowEvent {
  public:
    WindowMovedEvent(i32 xPos, i32 yPos)
      : WindowEvent{WindowEventType::Resize}, xPos_{xPos}, yPos_{yPos} {}

    [[nodiscard]] i32 xPos() const { return xPos_; }
    [[nodiscard]] i32 yPos() const { return yPos_; }

    [[nodiscard]] std::string toString() const override {
      std::stringstream ss;
      ss << "Event <Window> (MOVED: " << xPos_ << ", " << yPos_ << ")";
      return ss.str();
    }
  private:
    const i32 xPos_, yPos_;
  };
}