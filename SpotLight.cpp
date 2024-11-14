#include "SpotLight.h"

SpotLight::SpotLight(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& color,
    float intensity, float cutOff, float outerCutOff)
    : Light(position, color, intensity),
    direction(glm::normalize(direction)),
    cutOff(cutOff),
    outerCutOff(outerCutOff) {}

glm::vec3 SpotLight::getDirection() const {
    return direction;
}

void SpotLight::setDirection(const glm::vec3& dir) {
    direction = glm::normalize(dir);
    notifyObservers();
}

float SpotLight::getCutOff() const {
    return cutOff;
}

float SpotLight::getOuterCutOff() const {
    return outerCutOff;
}

void SpotLight::setCutOff(float cutOff) {
    this->cutOff = cutOff;
    notifyObservers();
}

void SpotLight::setOuterCutOff(float outerCutOff) {
    this->outerCutOff = outerCutOff;
    notifyObservers();
}


