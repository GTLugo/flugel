//
// Created by galex on 4/2/2022.
//

#pragma once

#include "core/callbacks/event_system.hpp"
#include "core/callbacks/notifier/notifier.hpp"

namespace ff {
  template<class C>
  class Subscribable {
    template<class E>
    class Subscriber {
    public:
      explicit Subscriber(C* object)
          : object_{object},
            id_{object->template subscribe<E>(FF_LAMBDA(onAppEvent))}{
        Log::debug_e("Subscribed: <{0}> {1}", FF_STRINGIFY_VAL(E), id_);
      }
      virtual ~Subscriber() {
        Log::debug_e("Unsubscribed: <{0}> {1}", FF_STRINGIFY_VAL(E), id_);
        object_->template unsubscribe<E>(id_);
      }
    private:
      C* object_;
      UUID id_;
    };
  public:
    class MainEventSubscriber : Subscriber<MainEvent> {
    public:
      explicit MainEventSubscriber(C* object) : Subscriber<MainEvent>{object} {}
    protected:
      virtual bool onMainEvent(const MainEvent& e) { return false; }
    };

    class GameEventSubscriber : Subscriber<GameEvent> {
    public:
      explicit GameEventSubscriber(C* object) : Subscriber<GameEvent>{object} {}
    protected:
      virtual bool onGameEvent(const GameEvent& e) { return false; }
    };

    class WindowEventSubscriber : Subscriber<WindowEvent> {
    public:
      explicit WindowEventSubscriber(C* object) : Subscriber<WindowEvent>{object} {}
    protected:
      virtual bool onWindowEvent(const WindowEvent& e) { return false; }
    };

    class InputEventSubscriber : Subscriber<InputEvent> {
    public:
      explicit InputEventSubscriber(C* object) : Subscriber<InputEvent>{object} {}
    protected:
      virtual bool onInputEvent(const InputEvent& e) { return false; }
    };

    class FlugelEventSubscriber :
        public MainEventSubscriber,
        public GameEventSubscriber,
        public WindowEventSubscriber,
        public InputEventSubscriber {
    public:
      explicit FlugelEventSubscriber(C* object)
        : MainEventSubscriber{object},
          GameEventSubscriber{object},
          WindowEventSubscriber{object},
          InputEventSubscriber{object} {}
    };

    template<typename Event_t>
    UUID subscribe(typename Notifier<Event_t>::Callback callback) {
      FF_ASSERT_E(false, "Unknown event type!");
      return {};
    }
    template<>
    UUID subscribe<MainEvent>(Notifier<MainEvent>::Callback callback) {
      return mainNotifier_.subscribe(std::move(callback));
    }
    template<>
    UUID subscribe<GameEvent>(Notifier<GameEvent>::Callback callback) {
      return gameNotifier_.subscribe(std::move(callback));
    }
    template<>
    UUID subscribe<WindowEvent>(Notifier<WindowEvent>::Callback callback) {
      return windowNotifier_.subscribe(std::move(callback));
    }
    template<>
    UUID subscribe<InputEvent>(Notifier<InputEvent>::Callback callback) {
      return inputNotifier_.subscribe(std::move(callback));
    }

    template<typename Event_t>
    void unsubscribe(const UUID& id) {
      FF_ASSERT_E(false, "Unknown event type!");
    }
    template<>
    void unsubscribe<MainEvent>(const UUID& id) {
      mainNotifier_.unsubscribe(id);
    }
    template<>
    void unsubscribe<GameEvent>(const UUID& id) {
      gameNotifier_.unsubscribe(id);
    }
    template<>
    void unsubscribe<WindowEvent>(const UUID& id) {
      windowNotifier_.unsubscribe(id);
    }
    template<>
    void unsubscribe<InputEvent>(const UUID& id) {
      inputNotifier_.unsubscribe(id);
    }

  protected:
    Notifier<MainEvent>   mainNotifier_;
    Notifier<GameEvent>   gameNotifier_;
    Notifier<WindowEvent> windowNotifier_;
    Notifier<InputEvent>  inputNotifier_;
  };
}

