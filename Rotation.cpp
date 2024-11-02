#include "Rotation.h"

Rotation::Rotation() : rotation(glm::mat4(1.0f)) {}

void Rotation::setRotation(const glm::vec3& axis, float angle) {
    rotation = glm::rotate(rotation, angle, axis);
}

glm::mat4 Rotation::getMatrix() const {
    return rotation;
}
