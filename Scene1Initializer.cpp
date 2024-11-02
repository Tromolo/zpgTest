#include "Scene1Initializer.h"  
#include "Scene.h"        
#include "Model.h"

Scene1Initializer::Scene1Initializer(ShaderProgram* shaderProgram)
    : shaderProgram(shaderProgram) {}

void Scene1Initializer::initialize(Scene& scene) {
    scene.clearObjects();

    static float triangleVertices[] = {
        0.0f,  0.6667f, 0.0f,
       -0.25f, -0.3333f, 0.0f,
        0.25f, -0.3333f, 0.0f
    };

    Model* triangleModel = new Model(triangleVertices, nullptr, 3, false);

    DrawableObject* triangle = new DrawableObject(triangleModel, shaderProgram);

    scene.addObject(triangle);
}
