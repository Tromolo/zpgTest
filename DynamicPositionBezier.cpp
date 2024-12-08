#include "DynamicPositionBezier.h"

DynamicPositionBezier::DynamicPositionBezier(const std::vector<glm::vec3>& controlPoints, float speed)
    : DynamicPosition(0.0f, 0.0f, 0.0f, 0.0f, speed),
    controlPoints(controlPoints), t(0.0f) {

    if (controlPoints.size() != 4) {
        throw std::invalid_argument("Bezier curve requires 4 control points.");
    }
}

void DynamicPositionBezier::update(float deltaTime) {
    if (controlPoints.size() != 4) return;

    glm::mat4x3 controlMatrix(controlPoints[0], controlPoints[1], controlPoints[2], controlPoints[3]);

    glm::vec3 newPosition = calculateBezierPosition(bezierBasisMatrix, controlMatrix, t);

    setPosition(newPosition);

    t += speed * deltaTime;
    if (t > 1.0f) {
        t = 0.0f;
    }
}

glm::vec3 DynamicPositionBezier::calculateBezierPosition(const glm::mat4& basisMatrix, const glm::mat4x3& controlMatrix, float t) {
    glm::vec4 parameterVector(t * t * t, t * t, t, 1.0f);
    return parameterVector * basisMatrix * glm::transpose(controlMatrix);
}
