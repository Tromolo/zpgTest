#include "Scene.h"
#include "SceneInitializer.h"

Scene::Scene(const std::vector<ShaderProgram*>& shaderPrograms, Camera& cam, int width, int height)
    : shaderPrograms(shaderPrograms), camera(cam), width(width), height(height) {}

Scene::~Scene() {
    clearObjects();
}

void Scene::initialize(SceneInitializer& initializer) {
    initializer.initialize(*this);
}

void Scene::render(Camera& camera) {
    glm::mat4 viewMatrix = camera.GetViewMatrix();
    float aspectRatio = static_cast<float>(width) / height;
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
    glm::vec3 cameraPosition = camera.Position;

    std::cout << "Number of lights in scene: " << lightSources.size() << std::endl;

    for (auto& shaderProgram : shaderPrograms) {
        shaderProgram->update(viewMatrix, cameraPosition);
        if (!lightSources.empty()) {
            shaderProgram->updateLight(*lightSources[0]);
        }
    }

    for (auto& object : objects) {
        if (!lightSources.empty()) {
            object->setupUniforms(viewMatrix, projection, cameraPosition, *lightSources[0]);
        }
        else {
            object->setupUniforms(viewMatrix, projection);
        }
        object->draw();
    }
}

void Scene::clearObjects() {
    for (auto& obj : objects) {
        delete obj;
    }
    objects.clear();
}

void Scene::addObject(DrawableObject* object) {
    objects.push_back(object);
}

void Scene::addLightSource(Light* light) {
    lightSources.push_back(light);
}

const std::vector<Light*>& Scene::getLightSources() const {
    return lightSources;
}

Camera& Scene::getCamera() {
    return camera;
}
