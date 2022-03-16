//
// Created by galex on 2/20/2022.
//

#include "camera.hpp"

#include "glm/gtc/matrix_transform.hpp"

namespace ff {
  Camera::Camera(float left, float right, float bottom, float top, float near_, float far_)
      : projMatrix_{glm::ortho(left, right, bottom, top, near_, far_)} {

  }

  Camera::Camera(float fovY, float aspectRatio, float near, float far) {

  }

  void Camera::recalculateViewMatrix() {
    viewMatrix_ = glm::inverse(transform_.matrix());
  }
}