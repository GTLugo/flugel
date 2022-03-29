//
// Created by galex on 2/20/2022.
//

#include "camera.hpp"

#include "core/renderer/renderer.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace ff {
  Camera::Camera(float left, float right, float bottom, float top, float near_, float far_)
      : projMatrix_{glm::ortho(left, right, bottom, top, near_, far_)} {
    recalculateViewMatrix();
  }

  Camera::Camera(float fovY, float aspectRatio, float near_, float far_)
      : projMatrix_{glm::perspective(fovY, aspectRatio, near_, far_)} {
    recalculateViewMatrix();
  }

  void Camera::recalculateViewMatrix() {
    viewMatrix_ = glm::inverse(transform_.matrix());
  }

  mat4 Camera::viewProjMatrix() const {
    switch (Renderer::api()) {
      case Renderer::API::None: {
        FF_ASSERT_E(false, "Running with no API not implemented!");
        return projMatrix_ * viewMatrix_;
      }
      case Renderer::API::OpenGL: {
        #if defined(FLUGEL_USE_OPENGL)
        return projMatrix_ * viewMatrix_;
        #else
        FF_ASSERT_E(false, "OpenGL not supported!");
        return mat4{1.f};
        #endif
      }
      case Renderer::API::Vulkan: {
        #if defined(FLUGEL_USE_VULKAN)
        FF_ASSERT_E(false, "Vulkan not implemented!");
        return projMatrix_ * viewMatrix_;
        #else
        FF_ASSERT_E(false, "Vulkan not supported!");
        return mat4{1.f};
        #endif
      }
      case Renderer::API::D3D11: {
        #if defined(FLUGEL_USE_D3D11)
        FF_ASSERT_E(false, "D3D11 not implemented!");
        return projMatrix_ * viewMatrix_;
        #else
        FF_ASSERT_E(false, "D3D11 not supported!");
        return mat4{1.f};
        #endif
      }
      default: {
        FF_ASSERT_E(false, "Unknown render api!");
        return projMatrix_ * viewMatrix_;
      }
    }
  }
}