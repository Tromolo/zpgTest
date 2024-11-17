#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "SpotLight.h"

void Renderer::render(const std::vector<std::shared_ptr<DrawableObject>>& objects,
    const std::vector<std::shared_ptr<ShaderProgram>>& shaderPrograms,
    const std::vector<std::shared_ptr<Light>>& lightSources,
    Camera& camera, float width, float height) {

    glm::mat4 viewMatrix = camera.GetViewMatrix();
    float aspectRatio = width / height;
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
    glm::vec3 cameraPosition = camera.Position;

    for (const auto& shaderProgram : shaderPrograms) {
        shaderProgram->update(viewMatrix, cameraPosition);        
        shaderProgram->updateLights(lightSources); //TODO: fix scene2 and you can remove this change Light in there for Point/Spot/Directional, not enough time now 
    }

    for (const auto& object : objects) {
        const auto& material = object->getMaterial(); 

        if (material) {
            for (const auto& shaderProgram : shaderPrograms) {
                shaderProgram->setMaterial(*material);
            }
        }

        object->setupUniforms(viewMatrix, projection, cameraPosition);

        object->draw();
    }
}
