#ifndef SCENE1INITIALIZER_H
#define SCENE1INITIALIZER_H

#include "SceneInitializer.h"
#include "ShaderProgram.h"
#include <memory>  // For std::shared_ptr

class Scene1Initializer : public SceneInitializer {
public:
    explicit Scene1Initializer(const std::shared_ptr<ShaderProgram>& shaderProgram);
    void initialize(Scene& scene) override;

private:
    std::shared_ptr<ShaderProgram> shaderProgram;
};

#endif
