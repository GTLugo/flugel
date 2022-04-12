#pragma once

#include "event.hpp"

namespace ff {
  class WindowEventBase : public EventBase {
  public:
    enum Action {
      None = 0,
      Close, Resize, Focus, Moved,
    };

    [[nodiscard]] Action action() const { return action_; }
    [[nodiscard]] std::string toString() const override {
      std::string name{"<WINDOW> "};
      switch (action_) {
        case Action::Close:     return name + "CLOSE";
        case Action::Resize:    return name + "RESIZE";
        case Action::Focus:     return name + "FOCUS";
        case Action::Moved:     return name + "MOVED";
        default:                return name + "UNKNOWN";
      }
    }
  protected:
    const Action action_;

    explicit WindowEventBase(Action action) : action_{action} {}
  };

  class WindowCloseEvent : public WindowEventBase {
  public:
    WindowCloseEvent() : WindowEventBase{Action::Close} {}
  };

  class WindowResizeEvent : public WindowEventBase {
  public:
    WindowResizeEvent(i32 width, i32 height)
      : WindowEventBase{Action::Resize}, width_{width}, height_{height} {}

    [[nodiscard]] i32 width() const { return width_; }
    [[nodiscard]] i32 height() const { return height_; }

    [[nodiscard]] std::string toString() const override {
      return WindowEventBase::toString() + " (" + std::to_string(width_) + ", " + std::to_string(height_) + ")";
    }
  private:
    const i32 width_, height_;
  };

  class WindowMovedEvent : public WindowEventBase {
  public:
    WindowMovedEvent(i32 xPos, i32 yPos)
      : WindowEventBase{Action::Resize}, xPos_{xPos}, yPos_{yPos} {}

    [[nodiscard]] i32 xPos() const { return xPos_; }
    [[nodiscard]] i32 yPos() const { return yPos_; }

    [[nodiscard]] std::string toString() const override {
      return WindowEventBase::toString() + " (" + std::to_string(xPos_) + ", " + std::to_string(yPos_) + ")";
    }
  private:
    const i32 xPos_, yPos_;
  };

  class WindowFocusEvent : public WindowEventBase {
  public:
    WindowFocusEvent(bool focused) : WindowEventBase{Action::Focus}, focused_{focused} {}

    [[nodiscard]] bool isFocused() const { return focused_; }

    [[nodiscard]] std::string toString() const override {
      return WindowEventBase::toString() + " (" + std::to_string(focused_) + ")";
    }
  private:
    bool focused_;
  };
}