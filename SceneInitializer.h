#ifndef SCENEINITIALIZER_H
#define SCENEINITIALIZER_H

#include "Scene.h"

class SceneInitializer {
public:
    virtual ~SceneInitializer() = default;

    virtual void initialize(Scene& scene) = 0;

    virtual void update(float deltaTime) {} 
};

#endif
