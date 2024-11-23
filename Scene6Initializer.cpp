#include "Scene6Initializer.h"
#include "Textures.h"
#include "Position.h"
#include "Scale.h"
#include "CompositeTransformation.h"
#include <glm/gtc/matrix_transform.hpp>

// Quad vertices for a plane (Position, UVs)
static float quadVertices[] = {
    // Positions          // Normals        // UVs
    -1.0f,  0.0f, -1.0f,   0.0f, 1.0f,  0.0f, 0.0f,  // Bottom-left
     1.0f,  0.0f, -1.0f,   0.0f, 1.0f,  1.0f, 0.0f,  // Bottom-right
    -1.0f,  0.0f,  1.0f,   0.0f, 1.0f,  0.0f, 1.0f,  // Top-left

     1.0f,  0.0f, -1.0f,   0.0f, 1.0f,  1.0f, 0.0f,  // Bottom-right
     1.0f,  0.0f,  1.0f,   0.0f, 1.0f,  1.0f, 1.0f,  // Top-right
    -1.0f,  0.0f,  1.0f,   0.0f, 1.0f,  0.0f, 1.0f   // Top-left
};


Scene6Initializer::Scene6Initializer(const std::vector<std::shared_ptr<ShaderProgram>>& shaders)
    : shaders(shaders) {}

void Scene6Initializer::initialize(Scene& scene) {
    scene.clearObjects();

    // Create a textured quad using the first shader
    createTexturedQuad(scene, shaders[1]); // Use the first shader for rendering
}

void Scene6Initializer::createTexturedQuad(Scene& scene, const std::shared_ptr<ShaderProgram>& shaderProgram) {
    // Load the texture
    GLuint textureID = Textures::loadTexture("test.png", true); // Ensure "test_png" is accessible

    // Create the quad model
    int quadVertexCount = sizeof(quadVertices) / (5 * sizeof(float)); // Each vertex has 5 floats
    auto quadModel = std::make_shared<Model>(quadVertices, nullptr, nullptr, quadVertexCount, true, POSITION | NORMAL | UV);

    // Create the drawable object
    auto quadObject = std::make_shared<DrawableObject>(quadModel, shaderProgram);
    quadObject->setTexture(textureID,false);

    auto compositeTransformation = std::make_shared<CompositeTransformation>();
    auto position = std::make_shared<Position>();
    position->setPosition(glm::vec3(0.0f, -1.0f, -3.0f)); // Position quad in front of the camera
    compositeTransformation->addTransformation(position);

    auto scale = std::make_shared<Scale>();
    scale->setScale(glm::vec3(5.0f)); // Make the quad larger
    compositeTransformation->addTransformation(scale);

    quadObject->setTransformation(compositeTransformation);




    // Add the quad to the scene
    scene.addObject(quadObject);
}

void Scene6Initializer::update(float deltaTime) {
    // No updates needed since there is no lighting or animations
}
