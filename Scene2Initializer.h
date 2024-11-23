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
#include "DynamicRotation.h"
#include "DynamicPosition.h"
#include "PointLight.h"

class Scene2Initializer : public SceneInitializer {
public:
    explicit Scene2Initializer(const std::vector<std::shared_ptr<ShaderProgram>>& scene2Shaders);

    void initialize(Scene& scene) override;
    void update(float deltaTime) override;
    void createGrassPlane(Scene& scene, const std::shared_ptr<ShaderProgram>& shaderProgram);
private:
    std::vector<std::shared_ptr<ShaderProgram>> scene2Shaders;
    std::vector<std::shared_ptr<DynamicRotation>> dynamicRotations;
    std::vector<std::shared_ptr<DynamicPosition>> dynamicPositions;
    std::vector<std::shared_ptr<DynamicPosition>> lightDynamicPositions;
    std::shared_ptr<PointLight> light1, light2;

    std::mt19937 randomEngine;
};

#endif
