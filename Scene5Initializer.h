#ifndef SCENE5INITIALIZER_H
#define SCENE5INITIALIZER_H

#include "SceneInitializer.h"
#include "ShaderProgram.h"
#include "Light.h"
#include "DrawableObject.h"
#include "DynamicPosition.h"
#include <memory>
#include <vector>
#include "SpotLight.h"
#include "DirectionalLight.h"
#include "DynamicRotation.h"
#include "PointLight.h"
#include "DynamicPositionBezier.h"

class Scene5Initializer : public SceneInitializer {
public:
    Scene5Initializer(const std::vector<std::shared_ptr<ShaderProgram>>& shaders);

    void initialize(Scene& scene) override;

    void update(float deltaTime) override;
    const std::shared_ptr<DrawableObject> getSkybox();
    void spawnTree(const glm::vec3& position, Scene& scene);
private:
    std::vector<std::shared_ptr<DynamicPositionBezier>> animators;
    std::vector<std::shared_ptr<ShaderProgram>> shaders; 
    std::vector<std::shared_ptr<DrawableObject>> dynamicBushes; 
    std::vector<std::shared_ptr<DynamicPosition>> dynamicPositions;
    std::vector<std::shared_ptr<DynamicRotation>> dynamicRotations;
    std::vector<std::shared_ptr<DynamicPosition>> lightDynamicPositions;
    std::shared_ptr<PointLight> light1, light2;
    std::shared_ptr<SpotLight> flashlight;
    std::shared_ptr<DirectionalLight> moonlight;
    std::shared_ptr<DrawableObject> skyboxObject;
    void addHouse(Scene& scene, const std::shared_ptr<ShaderProgram>& shaderProgram);
    void addLogin(Scene& scene, const std::shared_ptr<ShaderProgram>& shaderProgram);
    void addZombies(Scene& scene, const std::shared_ptr<ShaderProgram>& shaderProgram);
    void createSkybox(Scene& scene, const std::shared_ptr<ShaderProgram>& shaderProgram);
    void initializeForest(Scene& scene);
    void createGrassPlane(Scene& scene, const std::shared_ptr<ShaderProgram>& shaderProgram);
};

#endif 
