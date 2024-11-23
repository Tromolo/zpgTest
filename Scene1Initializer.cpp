#include "Scene1Initializer.h"
#include "Scene.h"
#include "Model.h"
#include "DrawableObject.h"
#include "CameraManager.h"
#include "CompositeTransformation.h"
#include "Position.h"

Scene1Initializer::Scene1Initializer(const std::shared_ptr<ShaderProgram>& shaderProgram)
    : shaderProgram(shaderProgram) {}

void Scene1Initializer::initialize(Scene& scene) {
    Camera& camera = CameraManager::getInstance().getCameraForScene(1);
    scene.clearObjects();

    static float triangleVertices[] = {
        0.0f,  0.6667f, 0.0f,
       -0.25f, -0.3333f, 0.0f,
        0.25f, -0.3333f, 0.0f
    };

    auto triangleModel = std::make_shared<Model>(triangleVertices, nullptr, nullptr, 3, false, POSITION);
    auto triangle = std::make_shared<DrawableObject>(triangleModel, shaderProgram);

    auto compositeTransformation = std::make_shared<CompositeTransformation>();

    auto position = std::make_shared<Position>();
    position->setPosition(glm::vec3(0.0f, 0.0f, 0.0f)); 
    compositeTransformation->addTransformation(position);

    triangle->setTransformation(compositeTransformation);

    scene.addObject(triangle);
}
