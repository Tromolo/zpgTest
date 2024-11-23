#include "Scene3Initializer.h"  
#include "Scene.h"              
#include "Model.h"               
#include "DrawableObject.h"    
#include <cmath>                
#include "CompositeTransformation.h"
#include "CameraManager.h"
#include "Position.h"
#include <memory> 



Scene3Initializer::Scene3Initializer(std::shared_ptr<ShaderProgram> sphereShader)
    : sphereShader(std::move(sphereShader)) {}

void Scene3Initializer::initialize(Scene& scene) {
    scene.clearObjects();

    Camera& camera = CameraManager::getInstance().getCameraForScene(3);

    auto pointLight = std::make_shared<PointLight>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 5.0f);
    pointLight->addObserver(sphereShader.get());
    scene.addLightSource(pointLight);

    int sphereVertexCount = sizeof(sphere) / sizeof(sphere[0]) / 6;
    auto sphereModel = std::make_shared<Model>(sphere, nullptr, nullptr, sphereVertexCount, true, POSITION | NORMAL);

    float radius = 2.5f;
    int numSpheres = 4;
    float angleStep = glm::radians(90.0f);

    for (int i = 0; i < numSpheres; ++i) {
        float angle = i * angleStep;
        glm::vec3 position(radius * cos(angle), 0.0f, radius * sin(angle));

        auto compositeTransformation = std::make_shared<CompositeTransformation>();

        auto positionTransformation = std::make_shared<Position>();
        positionTransformation->setPosition(position);
        compositeTransformation->addTransformation(positionTransformation);

        auto sphereObject = std::make_shared<DrawableObject>(sphereModel, sphereShader);
        sphereObject->setTransformation(compositeTransformation);

        scene.addObject(sphereObject);
    }
}
