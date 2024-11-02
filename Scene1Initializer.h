#ifndef SCENE1INITIALIZER_H
#define SCENE1INITIALIZER_H

#include "SceneInitializer.h"   
#include "ShaderProgram.h"     
#include "DrawableObject.h"

class Scene1Initializer : public SceneInitializer {
public:
    Scene1Initializer(ShaderProgram* shaderProgram);

    void initialize(Scene& scene) override;

private:
    ShaderProgram* shaderProgram;
};

#endif
