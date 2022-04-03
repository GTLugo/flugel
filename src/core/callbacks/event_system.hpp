//
// Created by galex on 3/27/2022.
//

#pragma once

#include "core/callbacks/events/event.hpp"

namespace ff {
  class EventSystem {
  public:
    using EventCallbackFn = std::function<void(const Event&)>;

    static void init(EventCallbackFn callbackFn) {
      if (instance_) return;
      Log::trace_e("Initializing Event System...");
      instance_ = new EventSystem{};
      instance_->eventCallback_ = std::move(callbackFn);
    }
    static void shutdown() { delete instance_; }

    static void handleEvent(const Event& e) {
      instance_->eventCallback_(e);
    }

    EventSystem(const EventSystem& other) = delete;
    EventSystem& operator=(const EventSystem& other) = delete;
  private:
    static inline EventSystem* instance_{nullptr};

    EventCallbackFn eventCallback_;

    EventSystem() = default;
    ~EventSystem() = default;
  };
}

