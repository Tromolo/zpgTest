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

class Scene5Initializer : public SceneInitializer {
public:
    Scene5Initializer(const std::vector<std::shared_ptr<ShaderProgram>>& shaders);

    void initialize(Scene& scene) override;

    void update(float deltaTime) override;

private:
    std::vector<std::shared_ptr<ShaderProgram>> shaders; 

    std::vector<std::shared_ptr<DrawableObject>> dynamicBushes; 
    std::vector<std::shared_ptr<DynamicPosition>> dynamicPositions;
    std::shared_ptr<SpotLight> flashlight;
    std::shared_ptr<DirectionalLight> moonlight;

    void initializeForest(Scene& scene);
    void createGrassPlane(Scene& scene, const std::shared_ptr<ShaderProgram>& shaderProgram);
};

#endif 
