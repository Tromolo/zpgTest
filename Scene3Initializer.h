#ifndef SCENE3INITIALIZER_H
#define SCENE3INITIALIZER_H

#include "SceneInitializer.h"
#include "ShaderProgram.h"    
#include "Light.h"             
#include <glm/glm.hpp>

class Scene3Initializer : public SceneInitializer {
public:
    Scene3Initializer(ShaderProgram* sphereShader);

    void initialize(Scene& scene) override;

private:
    ShaderProgram* sphereShader;
};

#endif
