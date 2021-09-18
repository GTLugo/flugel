#pragma once

#include "event.hpp"

namespace Flugel {
  class FLUGEL_API WindowResizeEvent : public Event {
  public:
    WindowResizeEvent(uint32_t width, uint32_t height)
      : width_{width}, height_{height} {}

    inline uint32_t getWidth() const { return width_; }
    inline uint32_t getHeight() const { return height_; }

    std::string toString() const override {
      std::stringstream ss;
      ss << "EVENT <" << getName() << "> (" << width_ << ", " << height_ << ")";
      return ss.str();
    }

    EVENT_CLASS_TYPE(WindowResize)
    EVENT_CLASS_CATEGORY(EventCategoryApp)
  private:
    uint32_t width_, height_;
  };

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

  class FLUGEL_API AppTickEvent : public Event {
  public:
    AppTickEvent() {}

    std::string toString() const override {
      std::stringstream ss;
      ss << "EVENT <" << getName() << ">";
      return ss.str();
    }

    EVENT_CLASS_TYPE(AppTick)
    EVENT_CLASS_CATEGORY(EventCategoryApp)
  };

  class FLUGEL_API AppUpdateEvent : public Event {
  public:
    AppUpdateEvent() {}

    std::string toString() const override {
      std::stringstream ss;
      ss << "EVENT <" << getName() << ">";
      return ss.str();
    }

    EVENT_CLASS_TYPE(AppUpdate)
    EVENT_CLASS_CATEGORY(EventCategoryApp)
  };

  class FLUGEL_API AppRenderEvent : public Event {
  public:
    AppRenderEvent() {}

    std::string toString() const override {
      std::stringstream ss;
      ss << "EVENT <" << getName() << ">";
      return ss.str();
    }

    EVENT_CLASS_TYPE(AppRender)
    EVENT_CLASS_CATEGORY(EventCategoryApp)
  };
}