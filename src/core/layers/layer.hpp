#pragma once

#include "core/callbacks/event_system.hpp"

#include "core/callbacks/subscribable.hpp"

namespace ff {
  class Layer : virtual public Subscribable<Layer> {
  public:
    explicit Layer(std::string name = "layer");
    virtual ~Layer();
    
    virtual void attach() {}
    virtual void detach() {}

    void toggle(bool enabled) { enabled_ = enabled; }
    [[nodiscard]] bool isEnabled() const { return enabled_; }

    [[nodiscard]] const std::string& name() const { return name_; }
    
    bool onEvent(const Event& e) { // https://www.cppstories.com/2018/09/visit-variants/
      if (!enabled_) return false;
      return std::visit(EventVisitor{
          [=](const MainEvent& event) { return onMainEvent_eng(event); },
          [=](const GameEvent& event) { return onGameEvent_eng(event); },
          [=](const WindowEvent& event) { return onWindowEvent_eng(event); },
          [=](const InputEvent& event) { return onInputEvent_eng(event); },
          [](const auto&) { return false; }
      }, e);
    }

  protected:
    std::string name_;
    bool enabled_{true};

    virtual bool onMainEvent(const MainEvent& e) { return false; }
    virtual bool onGameEvent(const GameEvent& e) { return false; }
    virtual bool onWindowEvent(const WindowEvent& e) { return false; }
    virtual bool onInputEvent(const InputEvent& e) { return false; }

  private:
    virtual bool onMainEvent_eng(const MainEvent& e);
    virtual bool onGameEvent_eng(const GameEvent& e);
    virtual bool onWindowEvent_eng(const WindowEvent& e);
    virtual bool onInputEvent_eng(const InputEvent& e);
  };
}