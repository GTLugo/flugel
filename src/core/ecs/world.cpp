//
// Created by galex on 3/30/2022.
//

#include "world.hpp"

namespace ff {
  bool World::onMainEvent(const MainEvent& e) {
    return false;
  }

  bool World::onGameEvent(const GameEvent& e) {
    return std::visit(EventVisitor{
        [=](const GameAwakeEvent&) {
          // Register systems
          ecs().registerSystem<CameraSystem>();
          ecs().registerSystem<RenderSystem>();

          return true;
        },
        [=](const GameStartEvent&) {
          ff::Log::debug_e("master_camera: {}", masterCamera_.id());
          masterCamera_.add<ff::Name>("master_camera")
              .add<ff::Transform>()
              .add<ff::Camera>(-1.f, 1.f, -1.f, 1.f, -1.f, 1.f);

          return true;
        },
        [=](const GameUpdateEvent&) {
          ecs().executeSystem<CameraSystem>();

          return true;
        },
        [=](const GameDrawEvent&) {
          ecs().executeSystem<RenderSystem>();

          return true;
        },
        [=](const GameStopEvent&) {
          masterCamera_.kill();

          return true;
        },
        [](const auto& event) { return false; }
    }, e);
  }

  bool World::onWindowEvent(const WindowEvent& e) {
    return false;
  }

  bool World::onInputEvent(const InputEvent& e) {
    return false;
  }
}