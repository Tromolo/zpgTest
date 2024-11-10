#ifndef SCENE3INITIALIZER_H
#define SCENE3INITIALIZER_H

#include "SceneInitializer.h"
#include "ShaderProgram.h"    
#include "Light.h"             
#include <glm/glm.hpp>
#include <memory>

class Scene3Initializer : public SceneInitializer {
public:
    explicit Scene3Initializer(std::shared_ptr<ShaderProgram> sphereShader);

    void initialize(Scene& scene) override;

private:
    std::shared_ptr<ShaderProgram> sphereShader;
};

#endif
