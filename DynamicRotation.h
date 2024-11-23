#ifndef DYNAMICROTATION_H
#define DYNAMICROTATION_H

#include "Rotation.h"
#include <glm/glm.hpp>

class DynamicRotation : public Rotation {
public:
    DynamicRotation(float speed, float amplitude, size_t index);

    void update(float time); 
    void setEnabled(bool enabled);
    bool isEnabled() const;
private:
    float speed;     
    float amplitude; 
    size_t index;
    bool enabled = true;
    float phase = 0.0f;
};

#endif
