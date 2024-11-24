#ifndef RENDERER_H
#define RENDERER_H

#include "Camera.h"
#include "Light.h"
#include "DrawableObject.h"
#include <vector>
#include <memory>
#include <glm/glm.hpp>

class Renderer {
public:
    void render(const std::vector<std::shared_ptr<DrawableObject>>& objects,
        const std::vector<std::shared_ptr<ShaderProgram>>& shaderPrograms,
        const std::vector<std::shared_ptr<Light>>& lightSources,
        Camera& camera, float width, float height);
    void renderSkybox(const std::shared_ptr<DrawableObject>& skybox, Camera& camera, float width, float height, bool skyboxRotationEnabled);
};

#endif
