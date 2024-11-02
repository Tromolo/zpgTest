#ifndef SCALE_H
#define SCALE_H

#include "Transformation.h"

class Scale : public Transformation {
public:
    Scale();
    void setScale(const glm::vec3& scale);
    glm::mat4 getMatrix() const override;

private:
    glm::vec3 scaling;
};

#endif
