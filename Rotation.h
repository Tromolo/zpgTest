#ifndef ROTATION_H
#define ROTATION_H

#include "Transformation.h"

class Rotation : public Transformation {
public:
    Rotation();
    void setRotation(const glm::vec3& axis, float angle);
    glm::mat4 getMatrix() const override;

private:
    glm::mat4 rotation;
};

#endif
