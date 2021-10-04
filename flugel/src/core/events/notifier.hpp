//
// Created by galex on 10/3/2021.
// resources: 
// https://www.youtube.com/watch?v=xnopUoZbMEk
// https://gameprogrammingpatterns.com/observer.html
// https://gameprogrammingpatterns.com/event-queue.html
// http://www.cs.sjsu.edu/~pearce/modules/patterns/events/pubsubimp.htm
// https://www.codeproject.com/Articles/1256352/CppEvent-How-to-implement-events-using-standard-cp#holdingEventHandlersTogether
// https://stackoverflow.com/questions/12988320/store-function-pointers-to-any-member-function
// https://en.cppreference.com/w/cpp/utility/functional/function
//

#pragma once

namespace Flugel {
  enum class EventType {
    None = 0,
    WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
    AppStart, AppTick, AppUpdateFixed, AppUpdate, AppRender, AppEnd,
    KeyPressed, KeyReleased,
    MousePressed, MouseReleased, MouseMoved, MouseScrolled,
  };

  enum EventCategory {
    None = 0,
    EventCategoryApp           = BIT(0),
    EventCategoryInput         = BIT(1),
    EventCategoryKeyboard      = BIT(2),
    EventCategoryMouse         = BIT(3),
  };

  #define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return EventType::##type; }\
                                 virtual EventType getEventType() const override { return getStaticType(); }\
                                 virtual const char* getName() const override { return #type; } 
  #define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }

  class FLUGEL_API Event {
  public:
    virtual EventType getEventType() const = 0;
    virtual const char* getName() const = 0;
    virtual int getCategoryFlags() const = 0;
    virtual std::string toString() const { return getName(); }

    inline bool isInCategory(const EventCategory& category) {
      return getCategoryFlags() & category;
    }
  };

  inline std::ostream& operator<<(std::ostream& out, const Event& e) {
    return out << e.toString();
  }

  // Notifier sends notifications for a single type of event
  // Usage: Create a member variable of this class in whatever class should be
  //        sending out notifications.
  template<typename Event_T>
  class FLUGEL_API Notifier {
    using EventFn = std::function<bool(Event_T&)>;
    /// TODO: change uint64_t for UUID
    using SubscriberCollection = std::map<UUID, EventFn>;
  public:
    Notifier() = default;
    virtual ~Notifier() {
      if (!subscribers_.empty()) {
        subscribers_.clear();
      }
    };

    // Subscribe and Unsubscribe should be given wrappers in the notifying class
    UUID subscribe(EventFn eventFn) {
      UUID id{};
      subscribers_.insert(std::pair<UUID, EventFn>(id, eventFn));
      FLUGEL_DEBUG_E("Subscribed: <{0}> {1}", Event_T::getStaticType(), id);
      return id;
    }

    void unsubscribe(const UUID& id) {
      subscribers_.erase(id);
      FLUGEL_DEBUG_E("Unsubscribed: <{0}> {1}", Event_T::getStaticType(), id);
    }

    // Notify should be called from within the class. It should never be called from
    // outside the class as that would introduce coupling and risk runaway events
    void notify(Event_T& event) {
      callSubscribers(event);
    }
  private:
    SubscriberCollection subscribers_;
  private:
    void callSubscribers(Event_T& event) {
      bool handled{false};
      for (auto& [id, sub] : subscribers_) {
        handled = sub(event);
        /// TODO: implement ordering events based on priority and skipping when handled already
        if (handled) {
          break;
        }
      }
    }
  };
}

