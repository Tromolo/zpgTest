#include "Scene4Initializer.h"  
#include "Scene.h"            
#include "Model.h"         
#include "DrawableObject.h"  
#include <glm/glm.hpp>      
#include <glm/gtc/matrix_transform.hpp>
#include <random>
#include <cmath>                
#include "CameraManager.h"

Scene4Initializer::Scene4Initializer(const std::vector<ShaderProgram*>& giftShaders)
    : giftShaders(giftShaders) {}

void Scene4Initializer::initialize(Scene& scene) {
    scene.clearObjects();

    Camera& camera = CameraManager::getInstance().getCameraForScene(4);

    Light* pointLight = new Light(glm::vec3(0.0f, 10.0f, 10.0f), glm::vec3(1.0f, 1.0f, 1.0f), 5.0f);
    for (ShaderProgram* shader : giftShaders) {
        pointLight->addObserver(shader);
    }
    scene.addLightSource(pointLight);

    int giftVertexCount = sizeof(gift) / sizeof(gift[0]) / 6;
    Model* giftModel = new Model(gift, nullptr, giftVertexCount, true);

    int numGifts = 15;
    float radius = 3.0f;
    float angleStep = glm::radians(360.0f / numGifts);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> shaderDist(0, giftShaders.size() - 1);

    for (int i = 0; i < numGifts; ++i) {
        float angle = i * angleStep;
        glm::vec3 position(radius * cos(angle), 0.0f, radius * sin(angle));

        int randomShaderIndex = shaderDist(gen);
        ShaderProgram* randomShader = giftShaders[randomShaderIndex];

        DrawableObject* giftObject = new DrawableObject(giftModel, randomShader);
        giftObject->getPosition()->setPosition(position);

        float scaleValue = 0.8f + i * 0.2f;
        giftObject->getScale()->setScale(glm::vec3(scaleValue));
        float rotationAngle = i * glm::radians(15.0f);
        giftObject->getRotation()->setRotation(glm::vec3(0.0f, 1.0f, 0.0f), rotationAngle);

        scene.addObject(giftObject);
    }
}
