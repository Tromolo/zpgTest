#ifndef SCENE2INITIALIZER_H
#define SCENE2INITIALIZER_H

#include "SceneInitializer.h"
#include "ShaderProgram.h"      
#include <glm/glm.hpp>          

class Scene2Initializer : public SceneInitializer {
public:
    Scene2Initializer(ShaderProgram* treeBushShader);

    void initialize(Scene& scene) override;

private:
    ShaderProgram* treeBushShader; 
};

#endif