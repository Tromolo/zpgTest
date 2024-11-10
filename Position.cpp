#include "Position.h"

Position::Position() : position(0.0f, 0.0f, 0.0f) {}

void Position::setPosition(const glm::vec3& pos) {
    position = pos;
}

glm::vec3 Position::getPosition() const
{
    return position;
}

glm::mat4 Position::getMatrix() const {
    return glm::translate(glm::mat4(1.0f), position);
}
