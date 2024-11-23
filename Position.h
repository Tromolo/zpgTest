#ifndef POSITION_H
#define POSITION_H

#include "Transformation.h"

class Position : public Transformation {
public:
    Position();
    void setPosition(const glm::vec3& pos);
    glm::vec3 getPosition() const;
    glm::mat4 getMatrix() const override;

protected:
    glm::vec3 position;
};

#endif
