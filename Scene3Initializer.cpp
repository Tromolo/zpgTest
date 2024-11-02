#include "Scene3Initializer.h"  
#include "Scene.h"              
#include "Model.h"               
#include "DrawableObject.h"    
#include <cmath>                
#include "CameraManager.h"

Scene3Initializer::Scene3Initializer(ShaderProgram* sphereShader)
    : sphereShader(sphereShader) {}

void Scene3Initializer::initialize(Scene& scene) {
    scene.clearObjects();

    Camera& camera = CameraManager::getInstance().getCameraForScene(3);

    Light* pointLight = new Light(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 5.0f);
    pointLight->addObserver(sphereShader);
    scene.addLightSource(pointLight);

    int sphereVertexCount = sizeof(sphere) / sizeof(sphere[0]) / 6;  
    Model* sphereModel = new Model(sphere, nullptr, sphereVertexCount, true);

    float radius = 2.5f;
    int numSpheres = 4;
    float angleStep = glm::radians(90.0f);

    for (int i = 0; i < numSpheres; ++i) {
        float angle = i * angleStep;
        glm::vec3 position(radius * cos(angle), 0.0f, radius * sin(angle));

        DrawableObject* sphereObject = new DrawableObject(sphereModel, sphereShader);
        sphereObject->getPosition()->setPosition(position);
        scene.addObject(sphereObject);
    }
          
}
