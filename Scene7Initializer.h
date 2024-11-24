#ifndef SCENE7INITIALIZER_H
#define SCENE7INITIALIZER_H

#include "SceneInitializer.h"
#include "ShaderProgram.h"
#include <memory>
#include "DynamicRotation.h"
#include "Controller.h"

class Scene7Initializer : public SceneInitializer {
public:
    explicit Scene7Initializer(const std::shared_ptr<ShaderProgram>& shaderProgram);
    void initialize(Scene& scene) override;
    void update(float deltaTime) override;
    void createSkybox(Scene& scene, const std::shared_ptr<ShaderProgram>& shaderProgram);
    const std::shared_ptr<DrawableObject> getSkybox() ;
private:
    GLuint loadCubemap(const std::vector<std::string>& faces);
    std::vector<std::shared_ptr<DynamicRotation>> dynamicRotations;
    std::shared_ptr<ShaderProgram> shaderProgram;
    Controller& controller;
    bool rotationEnabled = true;
    std::shared_ptr<DrawableObject> skyboxObject;
};

#endif
