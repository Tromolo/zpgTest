#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include "Light.h"

class DirectionalLight : public Light {
public:
    DirectionalLight(const glm::vec3& direction, const glm::vec3& color, float intensity);

    glm::vec3 getDirection() const;
    void setDirection(const glm::vec3& dir);

private:
    glm::vec3 direction;
};

#endif
