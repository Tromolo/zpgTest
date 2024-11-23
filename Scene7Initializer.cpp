#include "Scene7Initializer.h"
#include "Scene.h"
#include "CameraManager.h"
#include <GL/glew.h>
#include <SOIL.h>
#include <vector>
#include <iostream>
#include "Textures.h"
#include "Position.h"
#include "DynamicRotation.h"
#include "Scale.h"
#include <GLFW/glfw3.h>


float skycube[108] = {
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
};

Scene7Initializer::Scene7Initializer(const std::shared_ptr<ShaderProgram>& shaderProgram)
    : shaderProgram(shaderProgram), controller(controller) {}

void Scene7Initializer::initialize(Scene& scene) {
    scene.clearObjects();

    // Setup the skybox in the scene
    createSkybox(scene, shaderProgram);

    //std::cout << "Skybox initialized. Press 'T' to toggle camera following." << std::endl;
}

void Scene7Initializer::createSkybox(Scene& scene, const std::shared_ptr<ShaderProgram>& shaderProgram) {
    // Create model for the skybox
    auto skyboxModel = std::make_shared<Model>(skycube, nullptr, nullptr, 36, false, POSITION);

    // Load the cubemap texture
    GLuint cubemapTexture = loadCubemap({
        "posx.jpg", "negx.jpg",
        "posy.jpg", "negy.jpg",
        "posz.jpg", "negz.jpg"
        });

    auto skyboxObject = std::make_shared<DrawableObject>(skyboxModel, shaderProgram);
    skyboxObject->setTexture(cubemapTexture, true);

    auto compositeTransformation = std::make_shared<CompositeTransformation>();

    auto dynamicRotation = std::make_shared<DynamicRotation>(0.1f, glm::radians(360.0f), 0);
    compositeTransformation->addTransformation(dynamicRotation);

    auto scale = std::make_shared<Scale>();
    scale->setScale(glm::vec3(0.2f, 0.2f, 0.2f));
    compositeTransformation->addTransformation(scale);

    auto position = std::make_shared<Position>();
    position->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    compositeTransformation->addTransformation(position);

    skyboxObject->setTransformation(compositeTransformation);
    dynamicRotations.push_back(dynamicRotation);

    scene.addObject(skyboxObject);

}

void Scene7Initializer::update(float deltaTime) {
    if (Controller::getInstance()->isSkyboxRotationEnabled()) {
        for (auto& dynamicRotation : dynamicRotations) {
            dynamicRotation->update(deltaTime);
        }
    }
}



GLuint Scene7Initializer::loadCubemap(const std::vector<std::string>& faces) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    for (GLuint i = 0; i < faces.size(); i++) {
        int width, height, channels;
        unsigned char* data = SOIL_load_image(faces[i].c_str(), &width, &height, &channels, SOIL_LOAD_RGB);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            SOIL_free_image_data(data);
        }
        else {
            std::cerr << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            SOIL_free_image_data(data);
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}


void Scene7Initializer::setRotationEnabled(bool enabled) {
    this->rotationEnabled = enabled;
}