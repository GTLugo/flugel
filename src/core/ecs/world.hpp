//
// Created by galex on 3/30/2022.
//

#pragma once

#include "core/callbacks/event_system.hpp"

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
    [[nodiscard]] Entity& masterCamera() { return masterCamera_; }

    virtual bool onMainEvent(const MainEvent& e);
    virtual bool onGameEvent(const GameEvent& e);
    virtual bool onWindowEvent(const WindowEvent& e);
    virtual bool onInputEvent(const InputEvent& e);

    bool operator<(const World& rhs) const { return name_ < rhs.name_; }
    bool operator==(const World& rhs) const { return name_ == rhs.name_; }

  protected:
    [[nodiscard]] ECSManager& ecs() { return ecs_; }

  private:
    const std::string name_;
    ECSManager ecs_{};

    Entity masterCamera_{&ecs()};
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
