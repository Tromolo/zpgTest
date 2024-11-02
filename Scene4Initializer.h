#ifndef SCENE4INITIALIZER_H
#define SCENE4INITIALIZER_H

#include "SceneInitializer.h"
#include "ShaderProgram.h"    
#include <vector>

class Scene4Initializer : public SceneInitializer {
public:
    Scene4Initializer(const std::vector<ShaderProgram*>& giftShaders);

    void initialize(Scene& scene) override;

private:
    std::vector<ShaderProgram*> giftShaders;  
};

#endif
