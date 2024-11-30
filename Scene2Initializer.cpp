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
#include "Textures.h"
#include "Plain.h"
#include "PointLight.h"

Scene2Initializer::Scene2Initializer(const std::vector<std::shared_ptr<ShaderProgram>>& scene2Shaders)
    : scene2Shaders(scene2Shaders),
    randomEngine(std::random_device{}())
{}

void Scene2Initializer::initialize(Scene& scene) {
    scene.clearObjects();  
    dynamicRotations.clear();
    lightDynamicPositions.clear(); 
    Camera& camera = CameraManager::getInstance().getCameraForScene(2);

    auto grassShaderScene2 = scene2Shaders[1];
    createGrassPlane(scene, grassShaderScene2);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> posDist(-20.0f, 20.0f);
    std::uniform_real_distribution<float> rotDist(0.0f, glm::radians(360.0f));
    std::uniform_real_distribution<float> scaleDist(0.2f, 1.0f);

    glm::vec3 light1Pos = glm::vec3(0.0f, 2.0f, 0.0f);
    glm::vec3 light2Pos = glm::vec3(10.0f, 3.0f, -10.0f);

    light1 = std::make_shared<PointLight>(light1Pos, glm::vec3(1.0f, 0.0f, 0.0f), 4.0f);
    light2 = std::make_shared<PointLight>(light2Pos, glm::vec3(0.0f, 0.0f, 1.0f), 2.0f);

    for (const auto& shaderProgram : scene2Shaders) {
        light1->addObserver(shaderProgram.get());
        light2->addObserver(shaderProgram.get());
    }

    auto light1DynamicPosition = std::make_shared<DynamicPosition>(-20.0f, 20.0f, -20.0f, 20.0f, 1.0f);
    auto light2DynamicPosition = std::make_shared<DynamicPosition>(-20.0f, 20.0f, -20.0f, 20.0f, 1.0f);

    lightDynamicPositions.push_back(light1DynamicPosition);
    lightDynamicPositions.push_back(light2DynamicPosition);

    scene.addLightSource(light1);
    scene.addLightSource(light2);

    int treeVertexCount = sizeof(tree) / sizeof(tree[0]) / 6;
    auto treeModel = std::make_shared<Model>(tree, nullptr,nullptr, treeVertexCount, true, POSITION | NORMAL);

    int bushVertexCount = sizeof(bushes) / sizeof(bushes[0]) / 6;
    auto bushModel = std::make_shared<Model>(bushes, nullptr, nullptr, bushVertexCount, true, POSITION | NORMAL);

    int giftVertexCount = sizeof(gift) / sizeof(gift[0]) / 6;
    auto giftModel = std::make_shared<Model>(gift, nullptr, nullptr, giftVertexCount, true, POSITION | NORMAL);

    auto treeMaterial = std::make_shared<Material>(
        glm::vec3(0.2f, 0.5f, 0.2f),
        glm::vec3(0.3f, 0.6f, 0.3f),
        glm::vec3(0.1f, 0.1f, 0.1f),
        16.0f
    );


    auto bushMaterial = std::make_shared<Material>(
        glm::vec3(0.1f, 0.3f, 0.1f),
        glm::vec3(0.2f, 0.5f, 0.2f),
        glm::vec3(0.05f, 0.05f, 0.05f),
        8.0f
    );


    for (int i = 0; i < 50; ++i) {
        auto treeObject = std::make_shared<DrawableObject>(treeModel, scene2Shaders[0]);
        treeObject->setMaterial(treeMaterial);
        
        auto compositeTransformation = std::make_shared<CompositeTransformation>();
        auto position = std::make_shared<Position>();
        position->setPosition(glm::vec3(posDist(gen), 0.0f, posDist(gen)));
        compositeTransformation->addTransformation(position);

        auto scale = std::make_shared<Scale>();
        scale->setScale(glm::vec3(scaleDist(gen)));
        compositeTransformation->addTransformation(scale);

        if (i % 5 == 0) {
            auto dynamicRotation = std::make_shared<DynamicRotation>(1.0f, glm::radians(45.0f), i);
            compositeTransformation->addTransformation(dynamicRotation);
            dynamicRotations.push_back(dynamicRotation);
        }

        treeObject->setTransformation(compositeTransformation);
        scene.addObject(treeObject);
    }

    for (int i = 0; i < 50; ++i) {
        auto bushObject = std::make_shared<DrawableObject>(bushModel, scene2Shaders[0]);
        bushObject->setMaterial(bushMaterial);
        auto compositeTransformation = std::make_shared<CompositeTransformation>();

        if (i % 25 == 0) {
            auto dynamicPosition = std::make_shared<DynamicPosition>(-5.0f, 10.0f, -5.0f, 10.0f, 2.0f);
            compositeTransformation->addTransformation(dynamicPosition);
            dynamicPositions.push_back(dynamicPosition);
        }
        else {
            auto position = std::make_shared<Position>();
            position->setPosition(glm::vec3(posDist(gen), 0.0f, posDist(gen)));
            compositeTransformation->addTransformation(position);
        }

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

    for (auto& dynamicRotation : dynamicRotations) {
        dynamicRotation->update(deltaTime);
    }

    for (auto& dynamicPosition : dynamicPositions) {
        dynamicPosition->update(deltaTime);
    }

    for (size_t i = 0; i < lightDynamicPositions.size(); ++i) {
        lightDynamicPositions[i]->update(deltaTime);

        if (i == 0 && light1) {
            light1->setPosition(lightDynamicPositions[i]->getPosition());
        }
        else if (i == 1 && light2) {
            light2->setPosition(lightDynamicPositions[i]->getPosition());
        }
    }
}

void Scene2Initializer::createGrassPlane(Scene& scene, const std::shared_ptr<ShaderProgram>& shaderProgram) {
    GLuint grassTexture = Textures::loadTexture("grass.png", true);

    int vertexCount = sizeof(plain) / (8 * sizeof(float));
    auto grassPlaneModel = std::make_shared<Model>(plain, nullptr, nullptr, vertexCount, true, POSITION | NORMAL | UV);

    auto grassPlane = std::make_shared<DrawableObject>(grassPlaneModel, shaderProgram);

    grassPlane->setTexture(grassTexture, false);

    auto compositeTransformation = std::make_shared<CompositeTransformation>();
    auto position = std::make_shared<Position>();
    position->setPosition(glm::vec3(0.0f, -0.01f, 0.0f));
    compositeTransformation->addTransformation(position);

    grassPlane->setTransformation(compositeTransformation);

    scene.addObject(grassPlane);
}
