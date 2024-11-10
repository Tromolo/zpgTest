#ifndef SCENEINITIALIZER_H
#define SCENEINITIALIZER_H

#include "Scene.h"

class SceneInitializer {
public:
    virtual ~SceneInitializer() = default;

    virtual void initialize(Scene& scene) = 0;

    // New method to handle updates (e.g., animations, transformations)
    virtual void update(float deltaTime) {} // Default is no-op if not overridden
};

#endif
