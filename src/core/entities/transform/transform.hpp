//
// Created by galex on 3/14/2022.
//

#pragma once

namespace ff {
  class Transform {
  public:
    Transform() : position_{}, rotation_{}, scale_{1.f, 1.f, 1.f} {}
    Transform(const vec3& pos, const quat& rot, const vec3& scale = {1.f, 1.f, 1.f})
        : position_{pos}, rotation_{rot}, scale_{scale} {}

    void setPosition(const vec3& pos) { position_ = pos; }
    [[nodiscard]] const vec3& position() const { return position_; }

    void setRotation(const quat& rot) { rotation_ = rot; }
    [[nodiscard]] const quat& rotation() const { return rotation_; }

    void setScale(const vec3& scale) { scale_ = scale; }
    [[nodiscard]] const vec3& scale() const { return scale_; }

    mat4 matrix() {
      return glm::translate(MatId, position_)
             * glm::rotate(MatId, glm::eulerAngles(rotation_).z, vec3{0, 0, 1})
             * glm::rotate(MatId, glm::eulerAngles(rotation_).y, vec3{0, 1, 0})
             * glm::rotate(MatId, glm::eulerAngles(rotation_).x, vec3{1, 0, 0})
             * glm::scale(MatId, scale_);
    }
  private:
    vec3 position_;
    quat rotation_;
    vec3 scale_;
  };
}

