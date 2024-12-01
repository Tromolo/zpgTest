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

void Scene::render(Camera& camera, bool skyboxRotationEnabled) {
    auto skybox = getSkybox();
    renderer.render(objects, shaderPrograms, lightSources, camera, width, height, skybox, skyboxRotationEnabled);
}

void Scene::update(float deltaTime) {
    if (initializer) {
        initializer->update(deltaTime);
    }
}

size_t Scene::getLightSourceCount() const {
    return lightSources.size();
}

void Scene::clearObjects() {
    objects.clear(); 
    clearLightSources();
}

void Scene::clearLightSources() {
    lightSources.clear();
}

void Scene::addObject(std::shared_ptr<DrawableObject> object) {
    objects.push_back(object); 
}

void Scene::addLightSource(std::shared_ptr<Light> light) {
    lightSources.push_back(light);
}

const std::vector<std::shared_ptr<Light>>& Scene::getLightSources() const {
    return lightSources;
}


Camera& Scene::getCamera() {
    return camera;
}

std::shared_ptr<DrawableObject> Scene::getSkybox() const {
    return skybox;
}

void Scene::setSkybox(const std::shared_ptr<DrawableObject>& skyboxObj)
{
    skybox = skyboxObj;
}
