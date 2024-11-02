#ifndef POSITION_H
#define POSITION_H

#include "Transformation.h"

class Position : public Transformation {
public:
    Position();
    void setPosition(const glm::vec3& pos);
    glm::mat4 getMatrix() const override;

private:
    glm::vec3 position;
};

#endif
