#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transformation {
public:
    virtual ~Transformation() = default;

    virtual glm::mat4 getMatrix() const = 0; 
    //virtual void update(float deltaTime) = 0;
};

#endif
