#ifndef DYNAMICROTATION_H
#define DYNAMICROTATION_H

#include "Rotation.h"
#include <glm/glm.hpp>

class DynamicRotation : public Rotation {
public:
    DynamicRotation(float speed, float amplitude, size_t index);

    void update(float time); 

private:
    float speed;     
    float amplitude; 
    size_t index;
};

#endif
