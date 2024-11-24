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

void Renderer::renderSkybox(const std::shared_ptr<DrawableObject>& skybox, Camera& camera, float width, float height, bool skyboxRotationEnabled) {
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), width / height, 0.1f, 100.0f);

    if (skyboxRotationEnabled) {
        glm::mat4 viewMatrix = glm::mat4(glm::mat3(camera.GetViewMatrix()));
        auto skyboxShader = skybox->getShaderProgram();
        skyboxShader->use();
        skyboxShader->setUniforms(glm::mat4(1.0f), viewMatrix, projection);
    }
    else {
        glm::mat4 viewMatrix = camera.GetViewMatrix();
        auto skyboxShader = skybox->getShaderProgram();
        skyboxShader->use();
        skybox->setupUniforms(viewMatrix, projection, camera.Position);
    }

    glDepthFunc(GL_LEQUAL);
    skybox->draw();
    glDepthFunc(GL_LESS);
}

