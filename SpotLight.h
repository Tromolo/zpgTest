#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include "Light.h"

class SpotLight : public Light {
public:
    SpotLight(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& color,
        float intensity, float cutOff, float outerCutOff, float exponent);

    glm::vec3 getDirection() const;
    void setDirection(const glm::vec3& dir);

    float getCutOff() const;
    float getOuterCutOff() const;
    float getExponent() const;

    void setCutOff(float cutOff);
    void setOuterCutOff(float outerCutOff);
    void setExponent(float exp);

private:
    glm::vec3 direction;
    float cutOff;      
    float outerCutOff;  
    float exponent;
};

#endif
