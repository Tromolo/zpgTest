#ifndef DYNAMICPOSITION_H
#define DYNAMICPOSITION_H

#include "Position.h"
#include <glm/glm.hpp>
#include <random>

class DynamicPosition : public Position {
public:
    DynamicPosition(float minX, float maxX, float minZ, float maxZ, float speed);

    void update(float deltaTime);

private:
    float minX, maxX, minZ, maxZ;
    float speed;
    glm::vec3 direction;
    std::default_random_engine randomEngine;
    std::uniform_real_distribution<float> movementDist;
};

#endif
