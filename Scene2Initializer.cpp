#include "Scene2Initializer.h" 
#include "Scene.h"           
#include "Model.h"              
#include "DrawableObject.h"   
#include <random>   
#include <glm/gtc/matrix_transform.hpp> 
#include "CameraManager.h"
#include "CompositeTransformation.h"  
#include "Position.h"               
#include "Rotation.h"             
#include "Scale.h"     

static float grassPlaneVertices[] = {
    -20.0f, 0.0f, -20.0f,
     20.0f, 0.0f, -20.0f,
    -20.0f, 0.0f,  20.0f,

     20.0f, 0.0f, -20.0f,
     20.0f, 0.0f,  20.0f,
    -20.0f, 0.0f,  20.0f
};

Scene2Initializer::Scene2Initializer(const std::vector<ShaderProgram*>& scene2Shaders)
    : scene2Shaders(scene2Shaders) {}

void Scene2Initializer::initialize(Scene& scene) {
    scene.clearObjects();

    Camera& camera = CameraManager::getInstance().getCameraForScene(2);
  
    Model* grassPlaneModel = new Model(grassPlaneVertices, nullptr, 6, false);
    DrawableObject* grassPlane = new DrawableObject(grassPlaneModel, scene2Shaders[1]);
    scene.addObject(grassPlane);

    int treeVertexCount = sizeof(tree) / sizeof(tree[0]) / 6;
    Model* treeModel = new Model(tree, nullptr, treeVertexCount, true);

    int bushVertexCount = sizeof(bushes) / sizeof(bushes[0]) / 6;
    Model* bushModel = new Model(bushes, nullptr, bushVertexCount, true);

    int giftVertexCount = sizeof(gift) / sizeof(gift[0]) / 6;
    Model* giftModel = new Model(gift, nullptr, giftVertexCount, true);

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> posDistX(-20.0f, 20.0f);
    std::uniform_real_distribution<float> posDistZ(-20.0f, 20.0f);
    std::uniform_real_distribution<float> rotDist(0.0f, glm::radians(360.0f));
    std::uniform_real_distribution<float> scaleDist(0.2f, 1.0f);

    for (int i = 0; i < 50; ++i) {
        DrawableObject* treeObject = new DrawableObject(treeModel, scene2Shaders[0]);

        auto compositeTransformation = std::make_shared<CompositeTransformation>();

        auto position = std::make_shared<Position>();
        position->setPosition(glm::vec3(posDistX(gen), 0.0f, posDistZ(gen)));
        compositeTransformation->addTransformation(position);

        auto rotation = std::make_shared<Rotation>();
        rotation->setRotation(glm::vec3(0.0f, 1.0f, 0.0f), rotDist(gen));
        compositeTransformation->addTransformation(rotation);

        auto scale = std::make_shared<Scale>();
        scale->setScale(glm::vec3(scaleDist(gen)));
        compositeTransformation->addTransformation(scale);

        treeObject->setTransformation(compositeTransformation);
        scene.addObject(treeObject);
    }

    for (int i = 0; i < 50; ++i) {
        DrawableObject* bushObject = new DrawableObject(bushModel, scene2Shaders[0]);

        auto compositeTransformation = std::make_shared<CompositeTransformation>();

        auto position = std::make_shared<Position>();
        position->setPosition(glm::vec3(posDistX(gen), 0.0f, posDistZ(gen)));
        compositeTransformation->addTransformation(position);

        auto rotation = std::make_shared<Rotation>();
        rotation->setRotation(glm::vec3(0.0f, 1.0f, 0.0f), rotDist(gen));
        compositeTransformation->addTransformation(rotation);

        auto scale = std::make_shared<Scale>();
        scale->setScale(glm::vec3(scaleDist(gen)));
        compositeTransformation->addTransformation(scale);

        bushObject->setTransformation(compositeTransformation);
        scene.addObject(bushObject);
    }

    for (int i = 0; i < 20; ++i) {
        DrawableObject* giftObject = new DrawableObject(giftModel, scene2Shaders[0]);

        auto compositeTransformation = std::make_shared<CompositeTransformation>();

        auto position = std::make_shared<Position>();
        position->setPosition(glm::vec3(posDistX(gen), 0.0f, posDistZ(gen)));
        compositeTransformation->addTransformation(position);

        auto rotation = std::make_shared<Rotation>();
        rotation->setRotation(glm::vec3(0.0f, 1.0f, 0.0f), rotDist(gen));
        compositeTransformation->addTransformation(rotation);

        auto scale = std::make_shared<Scale>();
        scale->setScale(glm::vec3(scaleDist(gen)));
        compositeTransformation->addTransformation(scale);

        giftObject->setTransformation(compositeTransformation);
        scene.addObject(giftObject);
    }
}