#include "Scene.h"
#include "Model.h"
#include "DrawableObject.h"
#include <iostream>
#include "tree.h" 
#include "bushes.h"
#include "Sphere.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <random>
#include "Position.h"
#include "Scale.h"
#include "Rotation.h"
#include "gift.h"

Scene::Scene(const std::vector<ShaderProgram*>& shaderPrograms, Camera& cam, int width, int height)
    : shaderPrograms(shaderPrograms), camera(cam), width(width), height(height) {
}

void Scene::initializeScene1() {
    clearObjects();

    static float triangleVertices[] = {
        0.0f,  0.6667f, 0.0f,
       -0.25f, -0.3333f, 0.0f,
        0.25f, -0.3333f, 0.0f
    };

    Model* triangleModel = new Model(triangleVertices, nullptr,3, false);
    DrawableObject* triangle = new DrawableObject(triangleModel, shaderPrograms[1]);
    objects.push_back(triangle);
}

void Scene::initializeScene2() {
    clearObjects();

    int treeVertexCount = sizeof(tree) / sizeof(tree[0]) / 6;
    Model* treeModel = new Model(tree, nullptr, treeVertexCount, true);

    int bushVertexCount = sizeof(bushes) / sizeof(bushes[0]) / 6;
    Model* bushModel = new Model(bushes, nullptr, bushVertexCount, true);

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> posDistX(-20.0f, 20.0f);
    std::uniform_real_distribution<float> posDistY(-2.0f, 0.0f);
    std::uniform_real_distribution<float> posDistZ(-20.0f, 20.0f);
    std::uniform_real_distribution<float> rotDist(0.0f, glm::radians(360.0f));
    std::uniform_real_distribution<float> scaleDist(0.2f, 1.0f);

    for (int i = 0; i < 50; ++i) {
        DrawableObject* treeObject = new DrawableObject(treeModel, shaderPrograms[3]); 
        treeObject->getPosition()->setPosition(glm::vec3(posDistX(gen), posDistY(gen), posDistZ(gen)));
        treeObject->getRotation()->setRotation(glm::vec3(0.0f, 1.0f, 0.0f), rotDist(gen));
        treeObject->getScale()->setScale(glm::vec3(scaleDist(gen)));

        objects.push_back(treeObject);
    }

    for (int i = 0; i < 50; ++i) {
        DrawableObject* bushObject = new DrawableObject(bushModel, shaderPrograms[3]);
        bushObject->getPosition()->setPosition(glm::vec3(posDistX(gen), posDistY(gen), posDistZ(gen)));
        bushObject->getRotation()->setRotation(glm::vec3(0.0f, 1.0f, 0.0f), rotDist(gen));
        bushObject->getScale()->setScale(glm::vec3(scaleDist(gen)));

        objects.push_back(bushObject);
    }
}

void Scene::initializeScene3() {
    clearObjects();

    if (lightSources.empty()) {
        Light* pointLight = new Light(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 5.0f);
        pointLight->addObserver(shaderPrograms[4]);
        lightSources.push_back(pointLight);
    }

    int sphereVertexCount = sizeof(sphere) / sizeof(sphere[0]) / 6;
    Model* sphereModel = new Model(sphere, nullptr, sphereVertexCount, true);

    float radius = 2.5f;
    int numSpheres = 4;
    float angleStep = glm::radians(90.0f);

    for (int i = 0; i < numSpheres; ++i) {
        float angle = i * angleStep;
        glm::vec3 position(radius * cos(angle), 0.0f, radius * sin(angle));

        DrawableObject* sphereObject = new DrawableObject(sphereModel, shaderPrograms[4]);
        sphereObject->getPosition()->setPosition(position);
        objects.push_back(sphereObject);
    }

    camera = Camera(glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, -90.0f);
    camera.setTarget(glm::vec3(0.0f, 0.0f, 0.0f));
}

void Scene::initializeScene4()
{
    clearObjects();

    int giftVertexCount = sizeof(gift) / sizeof(gift[0]) / 6;
    Model* giftModel = new Model(gift, nullptr, giftVertexCount, true);

    int numGifts = 15;
    float radius = 3.0f; 
    float angleStep = glm::radians(360.0f / numGifts);  

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> shaderDist(4, 7);

    for (int i = 0; i < numGifts; ++i) {
        float angle = i * angleStep;

        glm::vec3 position(radius * cos(angle), 0.0f, radius * sin(angle));
        int randomShaderIndex = shaderDist(gen);
        DrawableObject* giftObject = new DrawableObject(giftModel, shaderPrograms[randomShaderIndex]);

        giftObject->getPosition()->setPosition(position);
        float scaleValue = 0.8f + i * 0.2f; 
        giftObject->getScale()->setScale(glm::vec3(scaleValue));
        float rotationAngle = i * glm::radians(15.0f);  
        giftObject->getRotation()->setRotation(glm::vec3(0.0f, 1.0f, 0.0f), rotationAngle);

        objects.push_back(giftObject);
    }
}

void Scene::clearObjects()
{
    for (auto& obj : objects) {
        delete obj;
    }
    objects.clear();
}

void Scene::render(Camera& camera) {

    //Camera& camera = CameraManager::getInstance().getCameraForScene(sceneId);

    glm::mat4 viewMatrix = camera.GetViewMatrix();
    float aspectRatio = static_cast<float>(width) / height;
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);

    glm::vec3 cameraPosition = camera.Position;

    bool hasLight = !lightSources.empty();

    for (auto& shaderProgram : shaderPrograms) {
        shaderProgram->update(viewMatrix, cameraPosition);
        if (hasLight) {
            shaderProgram->updateLight(*lightSources[0]);
        }
    }

    for (auto& object : objects) {
        if (hasLight) {
            object->setupUniforms(viewMatrix, projection, cameraPosition, *lightSources[0]);
        }
        else {
            object->setupUniforms(viewMatrix, projection);
        }
        object->draw();
    }
}

Scene::~Scene() {
    for (auto& obj : objects) {
        delete obj; 
    }
    objects.clear(); 
}


