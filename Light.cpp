#include "Light.h"

Light::Light(const glm::vec3& position, const glm::vec3& color, float intensity)
    : position(position), color(color), intensity(intensity) {}

glm::vec3 Light::getPosition() const {
    return position;
}

glm::vec3 Light::getColor() const {
    return color;
}

float Light::getIntensity() const {
    return intensity;
}

void Light::setPosition(const glm::vec3& pos) {
    position = pos;
    notifyObservers();
}

void Light::setColor(const glm::vec3& col) {
    color = col;
    notifyObservers();
}

void Light::setIntensity(float intensityValue) {
    intensity = intensityValue;
    notifyObservers();
}

void Light::addObserver(LightObserver* observer) {
    observers.push_back(observer);
}

void Light::notifyObservers() const {
    for (LightObserver* observer : observers) {
        observer->updateLight(*this);
    }
}