#include "Scene2Initializer.h" 
#include "Scene.h"           
#include "Model.h"              
#include "DrawableObject.h"   
#include <random>   
#include <glm/gtc/matrix_transform.hpp> 
#include "CameraManager.h"


Scene2Initializer::Scene2Initializer(ShaderProgram* treeBushShader)
    : treeBushShader(treeBushShader) {}

void Scene2Initializer::initialize(Scene& scene) {
    scene.clearObjects();

    Camera& camera = CameraManager::getInstance().getCameraForScene(2);
  
    int treeVertexCount = sizeof(tree) / sizeof(tree[0]) / 6;
    Model* treeModel = new Model(tree, nullptr, treeVertexCount, true);

    int bushVertexCount = sizeof(bushes) / sizeof(bushes[0]) / 6;
    Model* bushModel = new Model(bushes, nullptr, bushVertexCount, true);

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> posDistX(-20.0f, 20.0f);
    std::uniform_real_distribution<float> posDistZ(-20.0f, 20.0f);
    std::uniform_real_distribution<float> rotDist(0.0f, glm::radians(360.0f));
    std::uniform_real_distribution<float> scaleDist(0.2f, 1.0f);

    for (int i = 0; i < 50; ++i) {
        DrawableObject* treeObject = new DrawableObject(treeModel, treeBushShader);
        treeObject->getPosition()->setPosition(glm::vec3(posDistX(gen), 0.0f, posDistZ(gen)));
        treeObject->getRotation()->setRotation(glm::vec3(0.0f, 1.0f, 0.0f), rotDist(gen));
        treeObject->getScale()->setScale(glm::vec3(scaleDist(gen)));

        scene.addObject(treeObject);
    }

    for (int i = 0; i < 50; ++i) {
        DrawableObject* bushObject = new DrawableObject(bushModel, treeBushShader);
        bushObject->getPosition()->setPosition(glm::vec3(posDistX(gen), 0.0f, posDistZ(gen)));
        bushObject->getRotation()->setRotation(glm::vec3(0.0f, 1.0f, 0.0f), rotDist(gen));
        bushObject->getScale()->setScale(glm::vec3(scaleDist(gen)));

        scene.addObject(bushObject);
    }
}