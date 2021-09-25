#pragma once

#include "event.hpp"

namespace Flugel {
  class FLUGEL_API AppStartEvent : public Event {
  public:
    AppStartEvent() {}

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <" << getName() << ">";
      return ss.str();
    }

    EVENT_CLASS_TYPE(AppStart)
    EVENT_CLASS_CATEGORY(EventCategoryApp)
  };

  class FLUGEL_API AppTickEvent : public Event {
  public:
    AppTickEvent() {}

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <" << getName() << ">";
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
      ss << "Event <" << getName() << ">";
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
      ss << "Event <" << getName() << ">";
      return ss.str();
    }

    EVENT_CLASS_TYPE(AppRender)
    EVENT_CLASS_CATEGORY(EventCategoryApp)
  };

  class FLUGEL_API AppEndEvent : public Event {
  public:
    AppEndEvent() {}

    std::string toString() const override {
      std::stringstream ss;
      ss << "Event <" << getName() << ">";
      return ss.str();
    }

    EVENT_CLASS_TYPE(AppEnd)
    EVENT_CLASS_CATEGORY(EventCategoryApp)
  };
}