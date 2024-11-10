#include "Scene2Initializer.h" 
#include "Scene.h"           
#include "Model.h"              
#include "DrawableObject.h"    
#include <glm/gtc/matrix_transform.hpp> 
#include "CameraManager.h"
#include "CompositeTransformation.h"                          
#include "Scale.h"    
#include "Light.h"
#include <GLFW/glfw3.h>


static float grassPlaneVertices[] = {

    -20.0f, 0.0f, -20.0f,  0.0f, 1.0f, 0.0f,
     20.0f, 0.0f, -20.0f,  0.0f, 1.0f, 0.0f,
    -20.0f, 0.0f,  20.0f,  0.0f, 1.0f, 0.0f,

     20.0f, 0.0f, -20.0f,  0.0f, 1.0f, 0.0f,
     20.0f, 0.0f,  20.0f,  0.0f, 1.0f, 0.0f,
    -20.0f, 0.0f,  20.0f,  0.0f, 1.0f, 0.0f
};

Scene2Initializer::Scene2Initializer(const std::vector<std::shared_ptr<ShaderProgram>>& scene2Shaders)
    : scene2Shaders(scene2Shaders),
    randomEngine(std::random_device{}()), 
    movementDist(-0.1f, 0.1f),
    lightMovementDist(-0.3f, 0.3f)
{}

void Scene2Initializer::initialize(Scene& scene) {
    scene.clearObjects();

    Camera& camera = CameraManager::getInstance().getCameraForScene(2);

    auto grassShader = scene2Shaders[0];
    createGrassPlane(scene, grassShader);


    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> posDist(-20.0f, 20.0f);
    std::uniform_real_distribution<float> rotDist(0.0f, glm::radians(360.0f));
    std::uniform_real_distribution<float> scaleDist(0.2f, 1.0f);

    glm::vec3 light1Pos = glm::vec3(0.0f, 2.0f, 0.0f); 
    glm::vec3 light2Pos = glm::vec3(10.0f, 0.0f, -10.0f); 

    light1 = std::make_shared<Light>(light1Pos, glm::vec3(1.0f, 0.5f, 0.0f), 1.0f); // Orange 
    light2 = std::make_shared<Light>(light2Pos, glm::vec3(0.0f, 0.5f, 1.0f), 1.0f); // Blue 

    for (const auto& shaderProgram : scene2Shaders) {
        light1->addObserver(shaderProgram.get());
        light2->addObserver(shaderProgram.get());
    }

    scene.addLightSource(light1);
    scene.addLightSource(light2);

    int treeVertexCount = sizeof(tree) / sizeof(tree[0]) / 6;
    auto treeModel = std::make_shared<Model>(tree, nullptr, treeVertexCount, true);

    int bushVertexCount = sizeof(bushes) / sizeof(bushes[0]) / 6;
    auto bushModel = std::make_shared<Model>(bushes, nullptr, bushVertexCount, true);

    int giftVertexCount = sizeof(gift) / sizeof(gift[0]) / 6;
    auto giftModel = std::make_shared<Model>(gift, nullptr, giftVertexCount, true);

    for (int i = 0; i < 50; ++i) {
        auto treeObject = std::make_shared<DrawableObject>(treeModel, scene2Shaders[0]);
        auto compositeTransformation = std::make_shared<CompositeTransformation>();

        auto position = std::make_shared<Position>();
        position->setPosition(glm::vec3(posDist(gen), 0.0f, posDist(gen)));
        compositeTransformation->addTransformation(position);

        auto scale = std::make_shared<Scale>();
        scale->setScale(glm::vec3(scaleDist(gen)));
        compositeTransformation->addTransformation(scale);

        if (i % 5 == 0) {
            auto rotation = std::make_shared<Rotation>();
            dynamicRotations.push_back(rotation);
            compositeTransformation->addTransformation(rotation);
        }

        treeObject->setTransformation(compositeTransformation);
        scene.addObject(treeObject);
    }

    for (int i = 0; i < 50; ++i) {
        auto bushObject = std::make_shared<DrawableObject>(bushModel, scene2Shaders[0]);
        auto compositeTransformation = std::make_shared<CompositeTransformation>();

        auto position = std::make_shared<Position>();
        position->setPosition(glm::vec3(posDist(gen), 0.0f, posDist(gen)));
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
        auto giftObject = std::make_shared<DrawableObject>(giftModel, scene2Shaders[0]);
        auto compositeTransformation = std::make_shared<CompositeTransformation>();

        auto position = std::make_shared<Position>();
        position->setPosition(glm::vec3(posDist(gen), 0.0f, posDist(gen)));
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


void Scene2Initializer::update(float deltaTime) {
    float time = glfwGetTime();

    for (size_t i = 0; i < dynamicRotations.size(); ++i) {
        float angle = glm::radians(45.0f) * sin(time + i);
        dynamicRotations[i]->setRotation(glm::vec3(0.0f, 1.0f, 0.0f), angle);
    }

    if (movingBushPosition) {
        glm::vec3 currentPosition = movingBushPosition->getPosition();

        float offsetX = movementDist(randomEngine);
        float offsetZ = movementDist(randomEngine);

        glm::vec3 newPosition = currentPosition + glm::vec3(offsetX, 0.0f, offsetZ);

        newPosition.x = glm::clamp(newPosition.x, -20.0f, 20.0f);
        newPosition.z = glm::clamp(newPosition.z, -20.0f, 20.0f);

        movingBushPosition->setPosition(newPosition);
    }

    moveLight(light1);
    moveLight(light2);
}

void Scene2Initializer::moveLight(const std::shared_ptr<Light>& light) {
    glm::vec3 lightPos = light->getPosition();
    lightPos.x = glm::clamp(lightPos.x + lightMovementDist(randomEngine), -20.0f, 20.0f);
    lightPos.z = glm::clamp(lightPos.z + lightMovementDist(randomEngine), -20.0f, 20.0f);
    light->setPosition(lightPos);
}

void Scene2Initializer::createGrassPlane(Scene& scene, const std::shared_ptr<ShaderProgram>& shaderProgram) {
    auto grassPlaneModel = std::make_shared<Model>(grassPlaneVertices, nullptr, 6, true);

    auto grassPlane = std::make_shared<DrawableObject>(grassPlaneModel, shaderProgram);

    auto compositeTransformation = std::make_shared<CompositeTransformation>();
    auto position = std::make_shared<Position>();
    position->setPosition(glm::vec3(0.0f, -0.01f, 0.0f));
    compositeTransformation->addTransformation(position);
    grassPlane->setTransformation(compositeTransformation);

    scene.addObject(grassPlane);
}
