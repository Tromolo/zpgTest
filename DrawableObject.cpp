#include "DrawableObject.h"
#include "Light.h"
#include <glm/gtc/type_ptr.hpp>

DrawableObject::DrawableObject(Model* model, ShaderProgram* shaderProgram)
    : model(model), shaderProgram(shaderProgram), transformation(std::make_shared<CompositeTransformation>()) {}

DrawableObject::~DrawableObject() {
    if (model) {
        delete model;
        model = nullptr;
    }
}


void DrawableObject::draw() {

    model->draw();
}

ShaderProgram* DrawableObject::getShaderProgram() const
{
    return shaderProgram;
}

void DrawableObject::setTransformation(std::shared_ptr<CompositeTransformation> transformation) {
    this->transformation = transformation;
}

std::shared_ptr<CompositeTransformation> DrawableObject::getTransformation() const {
    return transformation;
}

void DrawableObject::setupUniforms(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const glm::vec3& cameraPosition, const Light& light) {
    glm::mat4 modelMatrix = transformation->getMatrix();
    glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelMatrix)));

    shaderProgram->use();
    shaderProgram->setUniforms(modelMatrix, viewMatrix, projectionMatrix);
    shaderProgram->setNormalMatrix(normalMatrix);

    shaderProgram->setVec3("lightPosition", light.getPosition());
    shaderProgram->setVec3("viewPosition", cameraPosition);
}

void DrawableObject::setupUniforms(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    glm::mat4 modelMatrix = transformation->getMatrix();

    glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelMatrix)));

    shaderProgram->use();
    shaderProgram->setUniforms(modelMatrix, viewMatrix, projectionMatrix);
    shaderProgram->setNormalMatrix(normalMatrix);

}