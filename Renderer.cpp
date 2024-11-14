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
        //cout << "Number of lights:"  << lightSources.size() << endl;
        if (!lightSources.empty()) {
            std::vector<Light*> rawLightPointers;
            for (const auto& light : lightSources) {
                rawLightPointers.push_back(light.get());

                /*if (auto spotLight = std::dynamic_pointer_cast<SpotLight>(light)) {
                    shaderProgram->updateSpotlight(
                        spotLight->getPosition(),
                        spotLight->getDirection(),
                        spotLight->getColor(),
                        spotLight->getIntensity(),
                        spotLight->getCutOff(),
                        spotLight->getOuterCutOff()
                    );
                }*/
            }
            shaderProgram->updateLights(rawLightPointers);
        }
    }

    for (const auto& object : objects) {
        object->setupUniforms(viewMatrix, projection, cameraPosition, lightSources);
        object->draw();
    }
}
