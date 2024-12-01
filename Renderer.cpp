#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "SpotLight.h"

void Renderer::render(const std::vector<std::shared_ptr<DrawableObject>>& objects,
    const std::vector<std::shared_ptr<ShaderProgram>>& shaderPrograms,
    const std::vector<std::shared_ptr<Light>>& lightSources,
    Camera& camera, float width, float height,
    const std::shared_ptr<DrawableObject>& skybox, bool skyboxRotationEnabled) {

    glm::mat4 viewMatrix = camera.GetViewMatrix();
    float aspectRatio = width / height;
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
    glm::vec3 cameraPosition = camera.Position;

    for (const auto& shaderProgram : shaderPrograms) {
        shaderProgram->update(viewMatrix, cameraPosition);        
        shaderProgram->updateLights(lightSources);
    }

    for (const auto& object : objects) {
        if (object == skybox && skyboxRotationEnabled) {
            continue;
        }
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

void Renderer::renderSkybox(const std::shared_ptr<DrawableObject>& skybox, Camera& camera, float width, float height) {
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), width / height, 0.1f, 100.0f);
    glm::mat4 viewMatrix = glm::mat4(glm::mat3(camera.GetViewMatrix()));
    auto skyboxShader = skybox->getShaderProgram();
    skyboxShader->use();
    glm::mat4 rotationTransform = glm::rotate(glm::mat4(1.0f), glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    skyboxShader->setUniforms(rotationTransform, viewMatrix, projection);


    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LEQUAL);
    skybox->draw();
    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
}

