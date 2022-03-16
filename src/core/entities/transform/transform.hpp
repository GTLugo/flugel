//
// Created by galex on 3/14/2022.
//

#pragma once

namespace ff {
  class Transform {
  public:
    Transform() : position_{}, rotation_{} {}
    Transform(const vec3& pos, const quat& rot)
        : position_{pos}, rotation_{rot} {}

    void setPosition(const vec3& pos) { position_ = pos; }
    [[nodiscard]] const vec3& position() const { return position_; }

    void setRotation(const quat& rot) { rotation_ = rot; }
    [[nodiscard]] const quat& rotation() const { return rotation_; }

    mat4 matrix() {
      return glm::translate(MatId, position_)
             * glm::rotate(MatId, glm::eulerAngles(rotation_).z, vec3{0, 0, 1})
             * glm::rotate(MatId, glm::eulerAngles(rotation_).y, vec3{0, 1, 0})
             * glm::rotate(MatId, glm::eulerAngles(rotation_).x, vec3{1, 0, 0});
    }
  private:
    vec3 position_;
    quat rotation_;
  };
}

