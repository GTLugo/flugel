//
// Created by galex on 3/30/2022.
//

#include "world.hpp"

namespace ff {
  bool World::onLogicEvent(const LogicEvent& e) {
    switch (e.action()) {
      case LogicEvent::Awake: {
        // Register systems
        ecs().registerSystem<CameraSystem>();
        ecs().registerSystem<RenderSystem>();
        break;
      }
      case LogicEvent::Start: {
        ff::Log::debug_e("master_camera: {}", camera_.id());
        camera_.add<ff::Name>("master_camera")
            .add<ff::Transform>()
            .add<ff::Camera>(-1.f, 1.f, -1.f, 1.f, -1.f, 1.f);
        break;
      }
      case LogicEvent::Update: {
        ecs().executeSystem<CameraSystem>();
        break;
      }
      case LogicEvent::Stop: {
        camera_.kill();
        break;
      }
      default: break;
    }
    return false;
  }

  bool World::onRenderEvent(const RenderEvent& e) {
    switch (e.action()) {
      case RenderEvent::AppStep: {
        ecs().executeSystem<RenderSystem>();
        break;
      }
      default: break;
    }
    return false;
  }
}