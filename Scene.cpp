#include "Scene.h"
#include "SceneInitializer.h"
#include <GLFW/glfw3.h>
#include "Rotation.h"

Scene::Scene(const std::vector<std::shared_ptr<ShaderProgram>>& shaderPrograms, Camera& camera, int width, int height)
    : shaderPrograms(shaderPrograms), camera(camera), width(width), height(height) {}

Scene::~Scene() {
    clearObjects();
}

void Scene::initialize(std::shared_ptr<SceneInitializer> initializer) {
    this->initializer = std::move(initializer); 
    this->initializer->initialize(*this);      
}

std::shared_ptr<SceneInitializer> Scene::getInitializer() const {
    return initializer; 
}

void Scene::render(Camera& camera) {
    glm::mat4 viewMatrix = camera.GetViewMatrix();
    float aspectRatio = static_cast<float>(width) / height;
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
    glm::vec3 cameraPosition = camera.Position;

    std::cout << "number of lights: " << lightSources.size() << std::endl;

    for (const auto& shaderProgram : shaderPrograms) {
        shaderProgram->update(viewMatrix, cameraPosition);

        if (!lightSources.empty()) {
            std::vector<Light*> rawLightPointers;
            for (const auto& light : lightSources) {
                rawLightPointers.push_back(light.get());
            }
            shaderProgram->updateLights(rawLightPointers); 
        }
    }

    for (const auto& object : objects) {
        if (lightSources.size() == 1) {
            object->setupUniformsL(viewMatrix, projection, cameraPosition, *lightSources[0]);
        }
        else {
            object->setupUniforms(viewMatrix, projection, cameraPosition, lightSources);
        }
        

        object->draw();
    }
}

void Scene::clearObjects() {
    objects.clear(); 
    lightSources.clear();
}

void Scene::addObject(std::shared_ptr<DrawableObject> object) {
    objects.push_back(object); 
}

void Scene::addLightSource(std::shared_ptr<Light> light) {
    lightSources.push_back(light);
}

Camera& Scene::getCamera() {
    return camera;
}

const std::vector<std::shared_ptr<Light>>& Scene::getLightSources() const {
    return lightSources;
}
