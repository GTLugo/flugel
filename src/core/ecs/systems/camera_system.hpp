//
// Created by galex on 4/3/2022.
//

#pragma once

#include "core/ecs/ecs.hpp"

namespace ff {
  class CameraSystem : public System<Transform, Camera> {
  public:
    void onUpdate() override;
  };
}
