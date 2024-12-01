#include "Scene7Initializer.h"
#include "Scene.h"
#include "CameraManager.h"
#include <GL/glew.h>
#include <SOIL.h>
#include <vector>
#include <iostream>
#include "Textures.h"
#include "Position.h"
#include "DynamicRotation.h"
#include "Scale.h"
#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "skycube.h"

Scene7Initializer::Scene7Initializer(const std::shared_ptr<ShaderProgram>& shaderProgram)
    : shaderProgram(shaderProgram), controller(controller) {}


void Scene7Initializer::initialize(Scene& scene) {
    scene.clearObjects();
    createSkybox(scene, shaderProgram);
}

void Scene7Initializer::createSkybox(Scene& scene, const std::shared_ptr<ShaderProgram>& shaderProgram) {
    auto skyboxModel = std::make_shared<Model>(skycube, nullptr, nullptr, 36, false, POSITION);

    GLuint cubemapTexture = Textures::loadCubemap({
        "posx.jpg", "negx.jpg",
        "posy.jpg", "negy.jpg",
        "posz.jpg", "negz.jpg"
        });

    if (cubemapTexture == 0) {
        std::cerr << "Failed to load skybox cubemap!" << std::endl;
        return;
    }

    skyboxObject = std::make_shared<DrawableObject>(skyboxModel, shaderProgram);
    skyboxObject->setTexture(cubemapTexture, true);

    auto compositeTransformation = std::make_shared<CompositeTransformation>();

    auto dynamicRotation = std::make_shared<DynamicRotation>(0.1f, glm::radians(360.0f), 0);
    compositeTransformation->addTransformation(dynamicRotation);

    auto scale = std::make_shared<Scale>();
    scale->setScale(glm::vec3(100.0f, 100.0f, 100.0f));
    compositeTransformation->addTransformation(scale);

    auto position = std::make_shared<Position>();
    position->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    compositeTransformation->addTransformation(position);

    skyboxObject->setTransformation(compositeTransformation);

    dynamicRotations.push_back(dynamicRotation);

    scene.addObject(skyboxObject);
}

const std::shared_ptr<DrawableObject> Scene7Initializer::getSkybox()
{
    return skyboxObject;
}


void Scene7Initializer::update(float deltaTime) {

}