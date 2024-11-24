#include "DynamicRotation.h"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include <iostream>

DynamicRotation::DynamicRotation(float speed, float amplitude, size_t index)
    : speed(speed), amplitude(amplitude), index(index) {}

void DynamicRotation::update(float deltaTime) {
    phase += speed * deltaTime;

    if (phase > glm::two_pi<float>()) {
        phase -= glm::two_pi<float>();
    }

    float angle = amplitude * glm::sin(phase + index);
    setRotation(glm::vec3(0.0f, 1.0f, 0.0f), angle);
}