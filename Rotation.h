#ifndef ROTATION_H
#define ROTATION_H

#include "Transformation.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Rotation : public Transformation {
public:
    void setRotation(const glm::vec3& axis, float angle);

    glm::mat4 getMatrix() const override;
protected:
    glm::vec3 axis = glm::vec3(0.0f, 1.0f, 0.0f);
    float angle = 0.0f;
};

#endif
