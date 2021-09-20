#include "transform_component.hpp"

namespace Flugel {
  glm::mat4 TransformComponent::mat4() {
    return glm::mat4{1};
  }
  
  glm::mat3 TransformComponent::normalMatrix() {
    return glm::mat3{1};
  }
}