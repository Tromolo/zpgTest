#include "Scale.h"

Scale::Scale() : scaling(1.0f, 1.0f, 1.0f) {}

void Scale::setScale(const glm::vec3& scale) {
    scaling = scale;
}

glm::mat4 Scale::getMatrix() const {
    return glm::scale(glm::mat4(1.0f), scaling);
}
