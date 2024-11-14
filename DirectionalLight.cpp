#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const glm::vec3& direction, const glm::vec3& color, float intensity)
    : Light(glm::vec3(0.0f), color, intensity), direction(glm::normalize(direction)) {}

glm::vec3 DirectionalLight::getDirection() const {
    return direction;
}

void DirectionalLight::setDirection(const glm::vec3& dir) {
    direction = glm::normalize(dir);
    notifyObservers();
}
