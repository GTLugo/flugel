//
// Created by galex on 3/30/2022.
//

#pragma once

#include "core/callbacks/events/event.hpp"
#include "core/callbacks/events/app_event.hpp"
#include "core/callbacks/events/render_event.hpp"
#include "core/callbacks/events/logic_event.hpp"
#include "core/callbacks/events/window_event.hpp"
#include "core/callbacks/events/keyboard_event.hpp"
#include "core/callbacks/events/mouse_event.hpp"

#include "ecs.hpp"

#include "core/layers/engine_layer.hpp"

#include "core/ecs/systems/camera_system.hpp"
#include "core/ecs/systems/render_system.hpp"

namespace ff {
  class World {
  public:
    explicit World(std::string name)
        : name_{std::move(name)} {}
    ~World() = default;

    [[nodiscard]] std::string name() const { return name_; }
    [[nodiscard]] Entity& camera() { return camera_; }

    virtual bool onAppEvent(const AppEvent& e) { return false; }
    virtual bool onLogicEvent(const LogicEvent& e);
    virtual bool onRenderEvent(const RenderEvent& e);
    virtual bool onWindowEvent(const WindowEvent& e) { return false; }
    virtual bool onKeyboardEvent(const KeyboardEvent& e) { return false; }
    virtual bool onMouseEvent(const MouseEvent& e) { return false; }
    virtual bool onCursorEvent(const CursorEvent& e) { return false; }
    virtual bool onScrollEvent(const ScrollEvent& e) { return false; }

    bool operator<(const World& rhs) const { return name_ < rhs.name_; }
    bool operator==(const World& rhs) const { return name_ == rhs.name_; }

  protected:
    [[nodiscard]] ECSManager& ecs() { return ecs_; }

  private:
    const std::string name_;
    ECSManager ecs_{};

    Entity camera_{&ecs()};
  };
}

// Allow hashing
namespace std {
  template<>
  struct hash<ff::World> {
    std::size_t operator()(const ff::World& world) const {
      return hash<std::string>()(world.name());
    }
  };
}
