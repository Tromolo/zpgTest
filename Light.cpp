#include "Light.h"
#include "SpotLight.h"
#include <iostream>
#include "DirectionalLight.h"
#include "PointLight.h"

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
        if (const auto* spotLight = dynamic_cast<const SpotLight*>(this)) {
            std::cout << "SpotLight observer notified." << std::endl;
            observer->updateLight(*spotLight);
        }
        else if (const auto* directionalLight = dynamic_cast<const DirectionalLight*>(this)) {
            std::cout << "DirectionalLight observer notified." << std::endl;
            observer->updateLight(*directionalLight);
        }
        else if (const auto& pointLight = dynamic_cast<const PointLight*>(this)){
            std::cout << "PointLight observer notified." << std::endl;
            observer->updateLight(*pointLight);
        }
    }
}

