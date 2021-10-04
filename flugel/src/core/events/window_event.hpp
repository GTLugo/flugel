#pragma once

#include "notifier.hpp"

namespace Flugel {
  class FLUGEL_API WindowCloseEvent : public Event {
  public:
    WindowCloseEvent() {}

    std::string toString() const override {
      std::stringstream ss;
      ss << "EVENT <" << getName() << ">";
      return ss.str();
    }

    EVENT_CLASS_TYPE(WindowClose)
    EVENT_CLASS_CATEGORY(EventCategoryApp)
  };

  class FLUGEL_API WindowResizeEvent : public Event {
  public:
    WindowResizeEvent(uint32_t width, uint32_t height)
      : width_{width}, height_{height} {}

    uint32_t getWidth() const { return width_; }
    uint32_t getHeight() const { return height_; }

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <" << getName() << "> (" << width_ << ", " << height_ << ")";
      return ss.str();
    }

    EVENT_CLASS_TYPE(WindowResize)
    EVENT_CLASS_CATEGORY(EventCategoryApp)
  private:
    uint32_t width_, height_;
  };

  class FLUGEL_API WindowMovedEvent : public Event {
  public:
    WindowMovedEvent(int xPos, int yPos)
      : xPos_{xPos}, yPos_{yPos} {}

    uint32_t getX() const { return xPos_; }
    uint32_t getY() const { return yPos_; }

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <" << getName() << "> (" << xPos_ << ", " << yPos_ << ")";
      return ss.str();
    }

    EVENT_CLASS_TYPE(WindowMoved)
    EVENT_CLASS_CATEGORY(EventCategoryApp)
  private:
    int xPos_, yPos_;
  };
}