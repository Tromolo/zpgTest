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
#include "Textures.h"
#include "Plain.h"
#include "skycube.h"


Scene5Initializer::Scene5Initializer(const std::vector<std::shared_ptr<ShaderProgram>>& shaders)
    : shaders(shaders) {}

void Scene5Initializer::initialize(Scene& scene) {
    scene.clearObjects();
    
    Camera& camera = CameraManager::getInstance().getCameraForScene(5);
    auto grassShaderScene5 = shaders[0];

    createGrassPlane(scene, grassShaderScene5);
    addHouse(scene, shaders[2]);
    addLogin(scene, shaders[3]);
    addZombies(scene, shaders[2]);
    initializeForest(scene);
    createSkybox(scene, shaders[4]);

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
        glm::vec3(0.6f, 0.6f, 0.8f),    
        10.0f                            
    );

    glm::vec3 light1Pos = glm::vec3(0.0f, 2.0f, 0.0f);
    glm::vec3 light2Pos = glm::vec3(10.0f, 3.0f, -10.0f);

    light1 = std::make_shared<PointLight>(light1Pos, glm::vec3(1.0f, 0.0f, 0.0f), 4.0f);
    light2 = std::make_shared<PointLight>(light2Pos, glm::vec3(0.0f, 0.0f, 1.0f), 2.0f);


    auto light1DynamicPosition = std::make_shared<DynamicPosition>(-20.0f, 20.0f, -20.0f, 20.0f, 1.0f);
    auto light2DynamicPosition = std::make_shared<DynamicPosition>(-20.0f, 20.0f, -20.0f, 20.0f, 1.0f);

    lightDynamicPositions.push_back(light1DynamicPosition);
    lightDynamicPositions.push_back(light2DynamicPosition);

    scene.addLightSource(light1);
    scene.addLightSource(light2);

    scene.addLightSource(flashlight);
    scene.addLightSource(moonlight);

    for (const auto& shaderProgram : shaders) {
        flashlight->addObserver(shaderProgram.get());
        moonlight->addObserver(shaderProgram.get());
        light1->addObserver(shaderProgram.get());
        light2->addObserver(shaderProgram.get());
    }
}

void Scene5Initializer::initializeForest(Scene& scene) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> posDist(-20.0f, 20.0f);
    std::uniform_real_distribution<float> scaleDist(0.2f, 1.0f);
    std::uniform_int_distribution<int> dynamicChance(0, 10);

    int treeVertexCount = sizeof(tree) / sizeof(tree[0]) / 6;
    auto treeModel = std::make_shared<Model>(tree, nullptr, nullptr, treeVertexCount, true, POSITION | NORMAL);

    int bushVertexCount = sizeof(bushes) / sizeof(bushes[0]) / 6;
    auto bushModel = std::make_shared<Model>(bushes, nullptr, nullptr, bushVertexCount, true, POSITION | NORMAL);

    auto treeMaterial1 = std::make_shared<Material>(
        glm::vec3(0.02f, 0.01f, 0.02f),
        glm::vec3(0.1f, 0.05f, 0.1f),
        glm::vec3(0.1f, 0.1f, 0.1f),
        16.0f
    );

    auto treeMaterial2 = std::make_shared<Material>(
        glm::vec3(0.03f, 0.02f, 0.01f),
        glm::vec3(0.15f, 0.1f, 0.05f),
        glm::vec3(0.1f, 0.1f, 0.1f),
        32.0f
    );


    auto treeShader = shaders[1];

    auto bushMaterial = std::make_shared<Material>(
        glm::vec3(0.02f, 0.03f, 0.02f),
        glm::vec3(0.1f, 0.2f, 0.1f),
        glm::vec3(0.05f, 0.05f, 0.05f), 
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

    for (auto& dynamicPosition : dynamicPositions) {
        dynamicPosition->update(deltaTime);
    }

    for (auto& dynamicRotation : dynamicRotations) {
        dynamicRotation->update(deltaTime);
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

    Camera& camera = CameraManager::getInstance().getCameraForScene(5);

    flashlight->setDirection(camera.Front);
    flashlight->setPosition(camera.Position);

}

const std::shared_ptr<DrawableObject> Scene5Initializer::getSkybox()
{
    return skyboxObject;
}

void Scene5Initializer::addZombies(Scene& scene, const std::shared_ptr<ShaderProgram>& shaderProgram) {
    auto zombieModel = std::make_shared<Model>("zombie.obj");

    GLuint zombieTexture = Textures::loadTexture("zombie.png", false);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> posXDist(-20.0f, 20.0f);
    std::uniform_real_distribution<float> posZDist(-20.0f, 20.0f);
    std::uniform_real_distribution<float> scaleDist(0.8f, 1.2f); 
    std::uniform_real_distribution<float> rotationDist(0.0f, glm::radians(360.0f));

    for (int i = 0; i < 10; ++i) {
        auto zombieObject = std::make_shared<DrawableObject>(zombieModel, shaderProgram);

        zombieObject->setTexture(zombieTexture, false);

        auto compositeTransformation = std::make_shared<CompositeTransformation>();

        auto position = std::make_shared<Position>();
        position->setPosition(glm::vec3(posXDist(gen), 0.0f, posZDist(gen))); 
        compositeTransformation->addTransformation(position);

        auto scale = std::make_shared<Scale>();
        scale->setScale(glm::vec3(scaleDist(gen))); 
        compositeTransformation->addTransformation(scale);

        auto rotation = std::make_shared<Rotation>();
        rotation->setRotation(glm::vec3(0.0f, 1.0f, 0.0f), rotationDist(gen));
        compositeTransformation->addTransformation(rotation);

        zombieObject->setTransformation(compositeTransformation);

        scene.addObject(zombieObject);
    }
}


void Scene5Initializer::addHouse(Scene& scene, const std::shared_ptr<ShaderProgram>& shaderProgram) {
    auto houseModel = std::make_shared<Model>("house.obj");

    auto houseObject = std::make_shared<DrawableObject>(houseModel, shaderProgram);

    GLuint houseTexture = Textures::loadTexture("house.png", true);
    houseObject->setTexture(houseTexture, false);

    auto compositeTransformation = std::make_shared<CompositeTransformation>();

    auto position = std::make_shared<Position>();
    position->setPosition(glm::vec3(0.0f, 0.0f, -24.0f)); 
    compositeTransformation->addTransformation(position);

    auto scale = std::make_shared<Scale>();
    scale->setScale(glm::vec3(1.0f, 1.0f, 1.0f)); 
    compositeTransformation->addTransformation(scale);

    auto rotation = std::make_shared<Rotation>();
    rotation->setRotation(glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(-90.0f));
    compositeTransformation->addTransformation(rotation);

    houseObject->setTransformation(compositeTransformation);

    scene.addObject(houseObject);
}

void Scene5Initializer::addLogin(Scene& scene, const std::shared_ptr<ShaderProgram>& shaderProgram) {
    auto hruModel = std::make_shared<Model>("HRU0273.obj");

    auto hruObject = std::make_shared<DrawableObject>(hruModel, shaderProgram);

    auto compositeTransformation = std::make_shared<CompositeTransformation>();

    auto position = std::make_shared<Position>();
    position->setPosition(glm::vec3(12.0f, 0.0f, -21.0f));
    compositeTransformation->addTransformation(position);

    auto scale = std::make_shared<Scale>();
    scale->setScale(glm::vec3(2.0f, 2.0f, 2.0f));
    compositeTransformation->addTransformation(scale);

    hruObject->setTransformation(compositeTransformation);

    scene.addObject(hruObject);
}


void Scene5Initializer::createGrassPlane(Scene& scene, const std::shared_ptr<ShaderProgram>& shaderProgram) {
    GLuint grassTexture = Textures::loadTexture("grass.png", true);


    int vertexCount = sizeof(plain) / (8 * sizeof(float));
    auto grassPlaneModel = std::make_shared<Model>(plain, nullptr, nullptr, vertexCount, true, POSITION | NORMAL | UV);

    auto grassPlane = std::make_shared<DrawableObject>(grassPlaneModel, shaderProgram);

    grassPlane->setTexture(grassTexture,false);

    auto compositeTransformation = std::make_shared<CompositeTransformation>();
    auto position = std::make_shared<Position>();
    position->setPosition(glm::vec3(0.0f, -0.01f, 0.0f));
    compositeTransformation->addTransformation(position);

    grassPlane->setTransformation(compositeTransformation);

    scene.addObject(grassPlane);
}

void Scene5Initializer::createSkybox(Scene& scene, const std::shared_ptr<ShaderProgram>& shaderProgram) {

    auto skyboxModel = std::make_shared<Model>(skycube, nullptr, nullptr, 36, false, POSITION);
    GLuint cubemapTexture = Textures::loadCubemap({
        "posx.jpg", "negx.jpg", "posy.jpg", "negy.jpg", "posz.jpg", "negz.jpg"
        });

    if (cubemapTexture == 0) {
        std::cerr << "Failed to load skybox cubemap!" << std::endl;
        return;
    }

    skyboxObject = std::make_shared<DrawableObject>(skyboxModel, shaderProgram);
    skyboxObject->setTexture(cubemapTexture, true);

    auto compositeTransformation = std::make_shared<CompositeTransformation>();
    auto position = std::make_shared<Position>();
    Camera& camera = CameraManager::getInstance().getCameraForScene(5);
    position->setPosition(camera.Position);

    compositeTransformation->addTransformation(position);

    auto dynamicRotation = std::make_shared<DynamicRotation>(0.1f, glm::radians(360.0f), 0);
    compositeTransformation->addTransformation(dynamicRotation);

    auto scale = std::make_shared<Scale>();
    scale->setScale(glm::vec3(100.0f, 100.0f, 100.0f));
    compositeTransformation->addTransformation(scale);

    skyboxObject->setTransformation(compositeTransformation);
    dynamicRotations.push_back(dynamicRotation);
    Textures::setCubemapParameters();
    scene.setSkybox(skyboxObject);
    scene.addObject(skyboxObject);
}