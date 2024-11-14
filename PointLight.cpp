#include "PointLight.h"

PointLight::PointLight(const glm::vec3& position, const glm::vec3& color, float intensity)
    : Light(position, color, intensity) {}
