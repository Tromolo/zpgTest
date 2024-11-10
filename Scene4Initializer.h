#ifndef SCENE4INITIALIZER_H
#define SCENE4INITIALIZER_H

#include "SceneInitializer.h"
#include "ShaderProgram.h"    
#include <vector>
#include <memory>

class Scene4Initializer : public SceneInitializer {
public:
    Scene4Initializer(const std::vector<std::shared_ptr<ShaderProgram>>& sphereShaders);

    void initialize(Scene& scene) override;

private:
    std::vector<std::shared_ptr<ShaderProgram>> sphereShaders;
};

#endif
