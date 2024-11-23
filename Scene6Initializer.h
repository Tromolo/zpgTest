#ifndef SCENE6INITIALIZER_H
#define SCENE6INITIALIZER_H

#include "Scene.h"
#include "ShaderProgram.h"
#include "SpotLight.h"
#include <vector>
#include <memory>
#include "SceneInitializer.h"

class Scene6Initializer : public SceneInitializer {
public:
    explicit Scene6Initializer(const std::vector<std::shared_ptr<ShaderProgram>>& shaders);

    void initialize(Scene& scene) override;
    void update(float deltaTime) override;

private:
    std::vector<std::shared_ptr<ShaderProgram>> shaders;

    void createTexturedQuad(Scene& scene, const std::shared_ptr<ShaderProgram>& shaderProgram);
};

#endif
