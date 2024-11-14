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
#include "CameraManager.h"

Scene4Initializer::Scene4Initializer(const std::vector<std::shared_ptr<ShaderProgram>>& sphereShaders)
    : sphereShaders(sphereShaders) {}

void Scene4Initializer::initialize(Scene& scene) {
    scene.clearObjects();

    Camera& camera = CameraManager::getInstance().getCameraForScene(4);

    auto pointLight = std::make_shared<PointLight>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 5.0f);
    for (const auto& shader : sphereShaders) {
        pointLight->addObserver(shader.get());
    }
    scene.addLightSource(pointLight);


    int sphereVertexCount = sizeof(sphere) / sizeof(sphere[0]) / 6;
    auto sphereModel = std::make_shared<Model>(sphere, nullptr, sphereVertexCount, true);

    int numSpheres = 5;
    float radius = 3.0f;
    float angleStep = glm::radians(360.0f / numSpheres);

    for (int i = 0; i < numSpheres; ++i) {
        float angle = i * angleStep;
        glm::vec3 position(radius * cos(angle), 0.0f, radius * sin(angle));

        auto chosenShader = sphereShaders[i % sphereShaders.size()];
        auto sphereObject = std::make_shared<DrawableObject>(sphereModel, chosenShader);

        auto compositeTransformation = std::make_shared<CompositeTransformation>();

        auto positionTransformation = std::make_shared<Position>();
        positionTransformation->setPosition(position);
        compositeTransformation->addTransformation(positionTransformation);

        float rotationAngle = i * glm::radians(15.0f);
        auto rotationTransformation = std::make_shared<Rotation>();
        rotationTransformation->setRotation(glm::vec3(0.0f, 1.0f, 0.0f), rotationAngle);
        compositeTransformation->addTransformation(rotationTransformation);

        sphereObject->setTransformation(compositeTransformation);

        scene.addObject(sphereObject);
    }
}
