//
// Created by galex on 3/30/2022.
//

#include "world.hpp"

namespace ff {
  bool World::onMainEvent(const MainEvent& e) {
    return false;
  }

  bool World::onGameEvent(const GameEvent& e) {
    switch (e.action()) {
      case GameEvent::Awake: {
        // Register systems
        ecs().registerSystem<CameraSystem>();
        ecs().registerSystem<RenderSystem>();
        break;
      }
      case GameEvent::Start: {
        ff::Log::debug_e("master_camera: {}", masterCamera_.id());
        masterCamera_.add<ff::Name>("master_camera")
            .add<ff::Transform>()
            .add<ff::Camera>(-1.f, 1.f, -1.f, 1.f, -1.f, 1.f);
        break;
      }
      case GameEvent::Update: {
        ecs().executeSystem<CameraSystem>();
        break;
      }
      case GameEvent::RenderGame: {
        ecs().executeSystem<RenderSystem>();
        break;
      }
      case GameEvent::Stop: {
        masterCamera_.kill();
        break;
      }
      default: break;
    }
    return false;
  }

  bool World::onWindowEvent(const WindowEvent& e) {
    return false;
  }

  bool World::onInputEvent(const InputEvent& e) {
    return false;
  }
}