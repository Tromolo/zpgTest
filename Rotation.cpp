#include "Rotation.h"

void Rotation::setRotation(const glm::vec3& axis, float angle) {
    this->axis = axis;
    this->angle = angle;
}

glm::mat4 Rotation::getMatrix() const {
    return glm::rotate(glm::mat4(1.0f), angle, axis);
}
