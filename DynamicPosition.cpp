#include "DynamicPosition.h"
#include <glm/gtc/random.hpp>
#include <glm/glm.hpp>

DynamicPosition::DynamicPosition(float minX, float maxX, float minZ, float maxZ, float speed)
    : minX(minX), maxX(maxX), minZ(minZ), maxZ(maxZ), speed(speed),
    movementDist(-1.0f, 1.0f), randomEngine(std::random_device{}()) {
    direction = glm::normalize(glm::vec3(movementDist(randomEngine), 0.0f, movementDist(randomEngine)));
}

void DynamicPosition::update(float deltaTime) {
    glm::vec3 currentPosition = getPosition();

    glm::vec3 offset = direction * speed * deltaTime;

    glm::vec3 newPosition = currentPosition + offset;

    newPosition.x = glm::clamp(newPosition.x, minX, maxX);
    newPosition.z = glm::clamp(newPosition.z, minZ, maxZ);

    setPosition(newPosition);

    if (newPosition.x <= minX || newPosition.x >= maxX || newPosition.z <= minZ || newPosition.z >= maxZ) {
        direction = glm::normalize(glm::vec3(movementDist(randomEngine), 0.0f, movementDist(randomEngine)));
    }
}
