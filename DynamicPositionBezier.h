#ifndef DYNAMICPOSITIONBEZIER_H
#define DYNAMICPOSITIONBEZIER_H

#include "DynamicPosition.h"
#include <vector>

class DynamicPositionBezier : public DynamicPosition {
public:
    DynamicPositionBezier(const std::vector<glm::vec3>& controlPoints, float speed);

    void update(float deltaTime);

private:
    std::vector<glm::vec3> controlPoints;
    float t;
    glm::mat4 bezierBasisMatrix = glm::mat4(
        glm::vec4(-1.0f, 3.0f, -3.0f, 1.0f),
        glm::vec4(3.0f, -6.0f, 3.0f, 0.0f),
        glm::vec4(-3.0f, 3.0f, 0.0f, 0.0f),
        glm::vec4(1.0f, 0.0f, 0.0f, 0.0f)
    );

    glm::vec3 calculateBezierPosition(const glm::mat4& basisMatrix, const glm::mat4x3& controlMatrix, float t);
};

#endif