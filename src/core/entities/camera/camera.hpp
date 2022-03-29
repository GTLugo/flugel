//
// Created by galex on 2/20/2022.
//

#pragma once

#include "core/entities/transform/transform.hpp"

namespace ff {
  class Camera {
  public:
    Camera(float left, float right, float bottom, float top, float near_, float far_);
    Camera(float fovY, float aspectRatio, float near_, float far_);

    void setPosition(const vec3& pos) { transform_.setPosition(pos); }
    [[nodiscard]] const vec3& position() const { return transform_.position(); }

    void setRotation(const quat& rot) { transform_.setRotation(rot); }
    [[nodiscard]] const quat& rotation() const { return transform_.rotation(); }

    [[nodiscard]] const mat4& projMat() const { return projMatrix_; }
    [[nodiscard]] const mat4& viewMat() const { return viewMatrix_; }

    [[nodiscard]] mat4 viewProjMatrix() const;
  private:
    bool mainCamera_{true};
    Transform transform_{};

    mat4 projMatrix_{};
    mat4 viewMatrix_{};

    void recalculateViewMatrix();
  };
}

