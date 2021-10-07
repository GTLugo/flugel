#pragma once

#include "notifier.hpp"

namespace Flugel {
  class FLUGEL_API WindowEvent : public Event {
  public:
    EVENT_CATEGORY(Window)

    WindowEvent(WindowEventType type, WindowEventData state)
      : type_{type}, state_{state} {}

    WindowEventType type() const { return type_; }
    WindowEventData state() const { return state_; }

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <Window> (";
      switch (type_) {
        case WindowEventType::Close: {
          ss << "CLOSE)";
          break;
        }
        case WindowEventType::Resize: {
          ss << "RESIZE:" << state_.width << ", " << state_.height << ")";
          break;
        }
        case WindowEventType::Focus: {
          ss << "FOCUS)";
          break;
        }
        case WindowEventType::LostFocus: {
          ss << "LOST_FOCUS)";
          break;
        }
        case WindowEventType::Moved: {
          ss << "MOVED:" << state_.xPos << ", " << state_.yPos << ")";
          break;
        }
        default: {
          ss << "NULL)";
          break;
        }
      }
      return ss.str();
    }
  protected:
    WindowEventType type_;
    WindowEventData state_;
  };

  // class FLUGEL_API WindowCloseEvent : public WindowEvent {
  // public:
  //   WindowCloseEvent()
  //    : WindowEvent{WindowEventType::Close} {}

  //   std::string toString() const override {
  //     std::stringstream ss;
  //     ss << "Event <Window> (Close)";
  //     return ss.str();
  //   }
  // };

  // class FLUGEL_API WindowResizeEvent : public WindowEvent {
  // public:
  //   WindowResizeEvent(uint32_t width, uint32_t height)
  //     : WindowEvent{WindowEventType::Resize}, width_{width}, height_{height} {}

  //   uint32_t getWidth() const { return width_; }
  //   uint32_t getHeight() const { return height_; }

  //   std::string toString() const override {
  //     std::stringstream ss;
  //     ss << "Event <Window> (Resize: " << width_ << ", " << height_ << ")";
  //     return ss.str();
  //   }
  // private:
  //   uint32_t width_, height_;
  // };

  // class FLUGEL_API WindowMovedEvent : public WindowEvent {
  // public:
  //   WindowMovedEvent(int xPos, int yPos)
  //     : WindowEvent{WindowEventType::Resize}, xPos_{xPos}, yPos_{yPos} {}

  //   uint32_t getX() const { return xPos_; }
  //   uint32_t getY() const { return yPos_; }

  //   std::string toString() const override {
  //     std::stringstream ss;
  //     ss << "Event <Window> (Moved: " << xPos_ << ", " << yPos_ << ")";
  //     return ss.str();
  //   }
  // private:
  //   int xPos_, yPos_;
  // };
}