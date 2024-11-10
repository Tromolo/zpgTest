#ifndef SCENE2INITIALIZER_H
#define SCENE2INITIALIZER_H

#include "SceneInitializer.h"
#include "ShaderProgram.h"      
#include <glm/glm.hpp>          
#include "Light.h"
#include "Rotation.h"
#include <memory>
#include "Position.h"
#include <random>

class Scene2Initializer : public SceneInitializer {
public:
    explicit Scene2Initializer(const std::vector<std::shared_ptr<ShaderProgram>>& scene2Shaders);

    void initialize(Scene& scene) override;
    void update(float deltaTime) override;
    void moveLight(const std::shared_ptr<Light>& light);
    void createGrassPlane(Scene& scene, const std::shared_ptr<ShaderProgram>& shaderProgram);
private:
    std::vector<std::shared_ptr<ShaderProgram>> scene2Shaders;
    std::shared_ptr<Position> movingBushPosition;
    std::vector<std::shared_ptr<Rotation>> dynamicRotations;
    std::shared_ptr<Light> light1, light2;
    std::uniform_real_distribution<float> lightMovementDist;

    std::mt19937 randomEngine;
    std::uniform_real_distribution<float> movementDist;
};

#endif
