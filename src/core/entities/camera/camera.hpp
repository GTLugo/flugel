//
// Created by galex on 2/20/2022.
//

#pragma once

#include "core/entities/transform/transform.hpp"

namespace ff {
  class Camera {
  public:
    Camera(float left, float right, float bottom, float top, float near_ = -1.f, float far_ = 1.f);
    Camera(float fovY, float aspectRatio, float near, float far);

    void setPosition(const vec3& pos) { transform_.setPosition(pos); }
    [[nodiscard]] const vec3& position() const { return transform_.position(); }

    void setRotation(const quat& rot) { transform_.setRotation(rot); }
    [[nodiscard]] const quat& rotation() const { return transform_.rotation(); }

    [[nodiscard]] const mat4& projMat() const { return projMatrix_; }
    [[nodiscard]] const mat4& viewMat() const { return viewMatrix_; }
    [[nodiscard]] mat4 pvMat() const { return projMatrix_ * viewMatrix_; }
    [[nodiscard]] mat4 vpMat() const { return viewMatrix_ * projMatrix_; }
  private:
    bool mainCamera_{true};
    Transform transform_{};

    mat4 projMatrix_{};
    mat4 viewMatrix_{};
    // mat4 viewProjMatrix_{};

    void recalculateViewMatrix();
  };
}

