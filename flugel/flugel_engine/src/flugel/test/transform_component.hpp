#pragma once

#include <glm/gtc/matrix_transform.hpp>

namespace Flugel {
  struct TransformComponent {
    glm::vec3 position{};
    glm::vec3 scale{};
    glm::vec3 rotation{};

    glm::mat4 mat4();
    glm::mat3 normalMatrix();
  };
}