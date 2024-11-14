#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include "Light.h"

class SpotLight : public Light {
public:
    SpotLight(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& color,
        float intensity, float cutOff, float outerCutOff);

    glm::vec3 getDirection() const;
    void setDirection(const glm::vec3& dir);

    float getCutOff() const;
    float getOuterCutOff() const;

    void setCutOff(float cutOff);
    void setOuterCutOff(float outerCutOff);

private:
    glm::vec3 direction;
    float cutOff;       // Cosine of inner cutoff angle
    float outerCutOff;  // Cosine of outer cutoff angle
};

#endif
