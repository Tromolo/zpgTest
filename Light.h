#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
#include "LightObserver.h"
#include <vector>

class Light {
public:
    Light(const glm::vec3& position, const glm::vec3& color, float intensity);
    virtual ~Light() = default;
    glm::vec3 getPosition() const;
    glm::vec3 getColor() const;
    float getIntensity() const;

    void setPosition(const glm::vec3& pos);
    void setColor(const glm::vec3& col);
    void setIntensity(float intensity);

    void addObserver(LightObserver* observer);
    void notifyObservers() const;

    virtual void update(float deltaTime) {}
private:
    glm::vec3 position;
    glm::vec3 color;
    float intensity;

    std::vector<LightObserver*> observers;
};

#endif
