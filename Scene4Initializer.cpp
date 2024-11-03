#include "Scene4Initializer.h"  
#include "Scene.h"            
#include "Model.h"         
#include "DrawableObject.h"  
#include "CompositeTransformation.h" 
#include "Position.h"                
#include "Rotation.h"                
#include "Scale.h"    
#include <glm/glm.hpp>      
#include <glm/gtc/matrix_transform.hpp>
#include <random>
#include <cmath>                
#include "CameraManager.h"

Scene4Initializer::Scene4Initializer(const std::vector<ShaderProgram*>& sphereShaders)
    : sphereShaders(sphereShaders) {}

void Scene4Initializer::initialize(Scene& scene) {
    scene.clearObjects();

    Camera& camera = CameraManager::getInstance().getCameraForScene(4);

    Light* pointLight = new Light(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 5.0f);
    for (ShaderProgram* shader : sphereShaders) {
        pointLight->addObserver(shader);  
    }
    scene.addLightSource(pointLight);


    int sphereVertexCount = sizeof(sphere) / sizeof(sphere[0]) / 6;
    Model* sphereModel = new Model(sphere, nullptr, sphereVertexCount, true);

    int numSpheres = 5;
    float radius = 3.0f;
    float angleStep = glm::radians(360.0f / numSpheres);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> shaderDist(0, sphereShaders.size() - 1);

    for (int i = 0; i < numSpheres; ++i) {
        float angle = i * angleStep;
        glm::vec3 position(radius * cos(angle), 0.0f, radius * sin(angle));

        ShaderProgram* chosenShader = sphereShaders[(i % 4)];

        DrawableObject* sphereObject = new DrawableObject(sphereModel, chosenShader);

        auto compositeTransformation = std::make_shared<CompositeTransformation>();

        auto positionTransformation = std::make_shared<Position>();
        positionTransformation->setPosition(position);
        compositeTransformation->addTransformation(positionTransformation);

        float scaleValue = 0.8f + i * 0.2f;
        auto scaleTransformation = std::make_shared<Scale>();
        scaleTransformation->setScale(glm::vec3(scaleValue));
        compositeTransformation->addTransformation(scaleTransformation);

        float rotationAngle = i * glm::radians(15.0f);
        auto rotationTransformation = std::make_shared<Rotation>();
        rotationTransformation->setRotation(glm::vec3(0.0f, 1.0f, 0.0f), rotationAngle);
        compositeTransformation->addTransformation(rotationTransformation);


        sphereObject->setTransformation(compositeTransformation);

        scene.addObject(sphereObject);
    }
}
