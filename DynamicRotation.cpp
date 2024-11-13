#include "DynamicRotation.h"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

DynamicRotation::DynamicRotation(float speed, float amplitude, size_t index)
    : speed(speed), amplitude(amplitude), index(index) {}

void DynamicRotation::update(float time) {
    float angle = amplitude * glm::sin(speed * time + index);
    setRotation(glm::vec3(0.0f, 1.0f, 0.0f), angle);
}
