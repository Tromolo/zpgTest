#include "Scene6Initializer.h"
#include "Scene.h"
#include "Position.h"
#include "Scale.h"
#include "CompositeTransformation.h"
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <SOIL.h>
#include <iostream>
#include "Textures.h"

float points[] = {
    0.000000f, -0.500000f,  0.500000f, -0.872900f, 0.218200f, 0.436400f, 0.836598f, 0.477063f,
    0.000000f,  0.500000f,  0.000000f, -0.872900f, 0.218200f, 0.436400f, 0.399527f, 0.286309f,
   -0.500000f, -0.500000f, -0.500000f, -0.872900f, 0.218200f, 0.436400f, 0.836598f, 0.000179f,
   -0.500000f, -0.500000f, -0.500000f,  0.000000f, -1.000000f, 0.000000f, 0.381686f, 0.999821f,
    0.500000f, -0.500000f, -0.500000f,  0.000000f, -1.000000f, 0.000000f, 0.000179f, 0.809067f,
    0.000000f, -0.500000f,  0.500000f,  0.000000f, -1.000000f, 0.000000f, 0.381686f, 0.522937f,
    0.500000f, -0.500000f, -0.500000f,  0.872900f, 0.218200f, 0.436400f, 0.399169f, 0.000179f,
    0.000000f,  0.500000f,  0.000000f,  0.872900f, 0.218200f, 0.436400f, 0.399169f, 0.522579f,
    0.000000f, -0.500000f,  0.500000f,  0.872900f, 0.218200f, 0.436400f, 0.000179f, 0.261379f,
   -0.500000f, -0.500000f, -0.500000f,  0.000000f, 0.447200f, -0.894400f, 0.788901f, 0.477421f,
    0.000000f,  0.500000f,  0.000000f,  0.000000f, 0.447200f, -0.894400f, 0.788901f, 0.999821f,
    0.500000f, -0.500000f, -0.500000f,  0.000000f, 0.447200f, -0.894400f, 0.399527f, 0.651554f
};

Scene6Initializer::Scene6Initializer(const std::vector<std::shared_ptr<ShaderProgram>>& shaders)
    : shaders(shaders) {}

void Scene6Initializer::initialize(Scene& scene) {
    scene.clearObjects();

    createTexture(scene, shaders[1]);
}

void Scene6Initializer::createTexture(Scene& scene, const std::shared_ptr<ShaderProgram>& shaderProgram) {

    GLuint textureID1 = Textures::loadTexture("wooden_fence.png", true);

    GLuint textureID2 = Textures::loadTexture("test.png", true);


    int quadVertexCount = sizeof(points) / (8 * sizeof(float));
    auto quadModel = std::make_shared<Model>(points, nullptr, nullptr, quadVertexCount, true, POSITION | NORMAL | UV);

    auto quadObject1 = std::make_shared<DrawableObject>(quadModel, shaderProgram);
    quadObject1->setTexture(textureID1, false);

    auto compositeTransformation1 = std::make_shared<CompositeTransformation>();
    auto position1 = std::make_shared<Position>();
    position1->setPosition(glm::vec3(-1.5f, 0.0f, -3.0f));
    compositeTransformation1->addTransformation(position1);

    auto scale1 = std::make_shared<Scale>();
    scale1->setScale(glm::vec3(2.0f));
    compositeTransformation1->addTransformation(scale1);

    quadObject1->setTransformation(compositeTransformation1);
    scene.addObject(quadObject1);

    auto quadObject2 = std::make_shared<DrawableObject>(quadModel, shaderProgram);
    quadObject2->setTexture(textureID2, false);

    auto compositeTransformation2 = std::make_shared<CompositeTransformation>();
    auto position2 = std::make_shared<Position>();
    position2->setPosition(glm::vec3(1.5f, 0.0f, -3.0f));
    compositeTransformation2->addTransformation(position2);

    auto scale2 = std::make_shared<Scale>();
    scale2->setScale(glm::vec3(2.0f));
    compositeTransformation2->addTransformation(scale2);

    quadObject2->setTransformation(compositeTransformation2);
    scene.addObject(quadObject2);
}


void Scene6Initializer::update(float deltaTime) {
}