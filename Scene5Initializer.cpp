#include "Scene5Initializer.h"
#include "Scene.h"
#include "CompositeTransformation.h"
#include "Position.h"
#include "Scale.h"
#include "Rotation.h"
#include "DynamicPosition.h"
#include <glm/gtc/matrix_transform.hpp>
#include <random>
#include "CameraManager.h"
#include "SpotLight.h"
#include <GLFW/glfw3.h>

static float grassPlaneVertices[] = {
    -20.0f, 0.0f, -20.0f,  0.0f, 1.0f, 0.0f,
     20.0f, 0.0f, -20.0f,  0.0f, 1.0f, 0.0f,
    -20.0f, 0.0f,  20.0f,  0.0f, 1.0f, 0.0f,

     20.0f, 0.0f, -20.0f,  0.0f, 1.0f, 0.0f,
     20.0f, 0.0f,  20.0f,  0.0f, 1.0f, 0.0f,
    -20.0f, 0.0f,  20.0f,  0.0f, 1.0f, 0.0f
};

Scene5Initializer::Scene5Initializer(const std::vector<std::shared_ptr<ShaderProgram>>& shaders)
    : shaders(shaders) {}

void Scene5Initializer::initialize(Scene& scene) {
    scene.clearObjects();
    
    Camera& camera = CameraManager::getInstance().getCameraForScene(5);
    
    createGrassPlane(scene, shaders[0]);
    initializeForest(scene);

    flashlight = std::make_shared<SpotLight>(
        camera.Position, 
        camera.Front,    
        glm::vec3(1.0f, 1.0f, 1.0f), 
        1.5f,                
        glm::cos(glm::radians(12.5f)),
        glm::cos(glm::radians(15.0f)), 
        10.0f                      
    );

    auto moonlight = std::make_shared<DirectionalLight>(
        glm::vec3(-0.2f, -1.0f, -0.3f),
        glm::vec3(1.0f, 0.0f, 0.0f),  
        2.7f                      
    );

    scene.addLightSource(flashlight);
    scene.addLightSource(moonlight);

    for (const auto& shaderProgram : shaders) {
        flashlight->addObserver(shaderProgram.get());
        moonlight->addObserver(shaderProgram.get());
    }
}

void Scene5Initializer::initializeForest(Scene& scene) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> posDist(-20.0f, 20.0f);
    std::uniform_real_distribution<float> scaleDist(0.2f, 1.0f);
    std::uniform_int_distribution<int> dynamicChance(0, 10);

    int treeVertexCount = sizeof(tree) / sizeof(tree[0]) / 6;
    auto treeModel = std::make_shared<Model>(tree, nullptr, treeVertexCount, true);

    int bushVertexCount = sizeof(bushes) / sizeof(bushes[0]) / 6;
    auto bushModel = std::make_shared<Model>(bushes, nullptr, bushVertexCount, true);

    auto treeMaterial1 = std::make_shared<Material>(
        glm::vec3(0.1f, 0.05f, 0.1f),
        glm::vec3(0.4f, 0.3f, 0.3f),
        glm::vec3(0.2f, 0.1f, 0.1f),
        16.0f
    );

    auto treeMaterial2 = std::make_shared<Material>(
        glm::vec3(0.2f, 0.1f, 0.05f),
        glm::vec3(0.5f, 0.4f, 0.3f),
        glm::vec3(0.3f, 0.2f, 0.1f),
        32.0f
    );

    auto treeShader = shaders[1];

    auto bushMaterial = std::make_shared<Material>(
        glm::vec3(0.05f, 0.1f, 0.05f),
        glm::vec3(0.3f, 0.5f, 0.3f),
        glm::vec3(0.2f, 0.2f, 0.1f),
        8.0f
    );
    auto bushShader = shaders[1]; 

    for (int i = 0; i < 50; ++i) {
        auto treeObject = std::make_shared<DrawableObject>(treeModel, treeShader);
        treeObject->setMaterial(i % 2 == 0 ? treeMaterial1 : treeMaterial2);
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

    for (int i = 0; i < 30; ++i) {
        auto bushObject = std::make_shared<DrawableObject>(bushModel, bushShader);
        bushObject->setMaterial(bushMaterial);
        auto compositeTransformation = std::make_shared<CompositeTransformation>();

        auto position = std::make_shared<Position>();
        position->setPosition(glm::vec3(posDist(gen), 0.0f, posDist(gen)));
        compositeTransformation->addTransformation(position);

        auto scale = std::make_shared<Scale>();
        scale->setScale(glm::vec3(scaleDist(gen)));
        compositeTransformation->addTransformation(scale);

        if (dynamicChance(gen) < 3) { 
            auto dynamicPosition = std::make_shared<DynamicPosition>(-5.0f, 10.0f, -5.0f, 10.0f, 2.0f);
            compositeTransformation->addTransformation(dynamicPosition);
            dynamicPositions.push_back(dynamicPosition);
        }

        bushObject->setTransformation(compositeTransformation);

        scene.addObject(bushObject);
        dynamicBushes.push_back(bushObject);
    }
}


void Scene5Initializer::update(float deltaTime) {
    float time = glfwGetTime();

    for (auto& dynamicPosition : dynamicPositions) {
        dynamicPosition->update(deltaTime);
    }

    for (auto& dynamicRotation : dynamicRotations) {
        dynamicRotation->update(time);
    }

    Camera& camera = CameraManager::getInstance().getCameraForScene(5);

    flashlight->setDirection(camera.Front);
    flashlight->setPosition(camera.Position);

}

void Scene5Initializer::createGrassPlane(Scene& scene, const std::shared_ptr<ShaderProgram>& shaderProgram) {
    auto grassPlaneModel = std::make_shared<Model>(grassPlaneVertices, nullptr, 6, true);

    auto grassPlane = std::make_shared<DrawableObject>(grassPlaneModel, shaderProgram);

    auto compositeTransformation = std::make_shared<CompositeTransformation>();
    auto position = std::make_shared<Position>();
    position->setPosition(glm::vec3(0.0f, -0.01f, 0.0f));
    compositeTransformation->addTransformation(position);
    grassPlane->setTransformation(compositeTransformation);

    scene.addObject(grassPlane);
}