#include "DynamicPositionBezier.h"

DynamicPositionBezier::DynamicPositionBezier(const std::vector<glm::vec3>& controlPoints, float speed)
    : DynamicPosition(0.0f, 0.0f, 0.0f, 0.0f, speed),
    controlPoints(controlPoints), t(0.0f) {

    if (controlPoints.size() != 4) {
        throw std::invalid_argument("Bezier curve requires exactly 4 control points.");
    }
}

void DynamicPositionBezier::update(float deltaTime) {
    if (controlPoints.size() != 4) return;

    // Create the control points matrix
    glm::mat4x3 controlMatrix(controlPoints[0], controlPoints[1], controlPoints[2], controlPoints[3]);

    // Calculate the new position using Bézier logic
    glm::vec3 newPosition = calculateBezierPosition(bezierBasisMatrix, controlMatrix, t);

    // Set the new position
    setPosition(newPosition);

    // Increment `t` and loop back if it exceeds 1
    t += speed * deltaTime;
    if (t > 1.0f) {
        t = 0.0f; // Reset for looping
    }
}

glm::vec3 DynamicPositionBezier::calculateBezierPosition(const glm::mat4& basisMatrix, const glm::mat4x3& controlMatrix, float t) {
    glm::vec4 parameterVector(t * t * t, t * t, t, 1.0f); // [t^3, t^2, t, 1]
    return parameterVector * basisMatrix * glm::transpose(controlMatrix);
}
