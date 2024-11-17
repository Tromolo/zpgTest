#include "SpotLight.h"

SpotLight::SpotLight(const glm::vec3& position, const glm::vec3& direction,
    const glm::vec3& color, float intensity, float cutOff,
    float outerCutOff, float exponent)
    : Light(position, color, intensity), direction(direction),
    cutOff(cutOff), outerCutOff(outerCutOff), exponent(exponent) {}

glm::vec3 SpotLight::getDirection() const {
    return glm::normalize(direction);
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

float SpotLight::getExponent() const {
    return exponent;
}

void SpotLight::setCutOff(float cutOff) {
    this->cutOff = cutOff;
    notifyObservers();
}

void SpotLight::setOuterCutOff(float outerCutOff) {
    this->outerCutOff = outerCutOff;
    notifyObservers();
}

void SpotLight::setExponent(float exp) {
    this->exponent = exp;
    notifyObservers();
}
