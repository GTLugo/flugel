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
// Notifier alerts its subscribers to an event occuring
//

#pragma once

#include "core/callbacks/events/event.hpp"

namespace ff {
  // Notifier sends notifications for a single type of event
  // Usage: Create a member variable of this class in whatever class should be
  //        sending out notifications.
  template<typename E>
  class Notifier {
  public:
    using Callback = std::function<bool(const E&)>;
    using SubscriberCollection = std::map<UUID, Callback>;

    Notifier() = default;
    virtual ~Notifier() {
      if (!subscribers_.empty()) {
        subscribers_.clear();
      }
    };

    // Subscribe and Unsubscribe should be given wrappers in the notifying class
    UUID subscribe(Callback callback) {
      UUID id{};
      subscribers_.insert(std::pair<UUID, Callback>(id, callback));
      return id;
    }

    void unsubscribe(const UUID& id) {
      subscribers_.erase(id);
    }

    // Notify should be called from within the class. It should never be called from
    // outside the class as that would introduce coupling and risk runaway events

    bool notify(const E& event) {
      bool handled{false};
      for (const auto& [id, sub] : subscribers_) {
        handled = sub(event);
      }
      return handled;
    }
  private:
    SubscriberCollection subscribers_;
  };

//  class NotifierNew {
//  public:
//    using EventFn = std::function<bool(const Event&)>;
//    using SubscriberCollection = std::map<UUID, EventFn>;
//
//    NotifierNew() = default;
//    virtual ~NotifierNew() {
//      if (!subscribers_.empty()) {
//        subscribers_.clear();
//      }
//    };
//
//    // Subscribe and Unsubscribe should be given wrappers in the notifying class
//    UUID subscribe(EventFn eventFn) {
//      UUID id{};
//      subscribers_.insert(std::pair<UUID, EventFn>(id, eventFn));
//      return id;
//    }
//
//    void unsubscribe(const UUID& id) {
//      subscribers_.erase(id);
//    }
//
//    // Notify should be called from within the class. It should never be called from
//    // outside the class as that would introduce coupling and risk runaway events
//
//    bool notify(const Event& event) {
//      bool handled{false};
//      for (const auto& [id, sub] : subscribers_) {
//        handled = sub(event);
//      }
//      return handled;
//    }
//  private:
//    SubscriberCollection subscribers_;
//  };
}

