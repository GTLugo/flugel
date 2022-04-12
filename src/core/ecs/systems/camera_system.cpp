//
// Created by galex on 4/3/2022.
//

#include "camera_system.hpp"


#include "core/threading/job_system.hpp"

namespace ff {
  void CameraSystem::onUpdate() {
    parallelFor([](Entity& entity) {
      auto& transform{entity.getRef<Transform>()};
      auto& camera{entity.getRef<Camera>()};
      camera.viewMatrix = glm::inverse(transform.matrix());
    });
  }
}