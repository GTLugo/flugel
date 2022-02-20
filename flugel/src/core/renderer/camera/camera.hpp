//
// Created by galex on 2/20/2022.
//

#pragma once

namespace fge {
  class Camera {
  public:
    Camera(float left, float right, float bottom, float top, float near, float far);
    Camera(float fovY, float aspectRatio, float near, float far);

    void setPos(const vec3& pos) { position_ = pos; }
    [[nodiscard]] const vec3& position() const { return position_; }

    void setRot(const vec3& rot) { rotation_ = rot; }
    [[nodiscard]] const vec3& rotation() const { return rotation_; }
  private:
    bool mainCamera_{true};
    vec3 position_{};
    vec3 rotation_{};

    mat4 projMatrix_{};
    mat4 viewMatrix_{};
    mat4 viewProjMatrix_{};
  };
}

