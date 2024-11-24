#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Light.h"

class PointLight : public Light {
public:
    PointLight(const glm::vec3& position, const glm::vec3& color, float intensity);

};

#endif
