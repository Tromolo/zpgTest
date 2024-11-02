#include "DrawableObject.h"
#include "Light.h"
#include <glm/gtc/type_ptr.hpp>

DrawableObject::DrawableObject(Model* model, ShaderProgram* shaderProgram)
    : model(model), shaderProgram(shaderProgram){

    position = new Position();
    rotation = new Rotation();
    scale = new Scale();
}

DrawableObject::~DrawableObject() {
    if (model) {
        delete model;
        model = nullptr;
    }

    delete position;
    delete rotation;
    delete scale;
}

Position* DrawableObject::getPosition() const {
    return position;
}

Rotation* DrawableObject::getRotation() const {
    return rotation;
}

Scale* DrawableObject::getScale() const {
    return scale;
}

void DrawableObject::draw() {

    model->draw();
}

ShaderProgram* DrawableObject::getShaderProgram() const
{
    return shaderProgram;
}

void DrawableObject::setupUniforms(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const glm::vec3& cameraPosition, const Light& light) {
    glm::mat4 modelMatrix = position->getMatrix() * rotation->getMatrix() * scale->getMatrix();
    glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelMatrix)));

    shaderProgram->use();
    shaderProgram->setUniforms(modelMatrix, viewMatrix, projectionMatrix);
    shaderProgram->setNormalMatrix(normalMatrix);

    shaderProgram->setVec3("lightPosition", light.getPosition());
    shaderProgram->setVec3("viewPosition", cameraPosition);
}

void DrawableObject::setupUniforms(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    glm::mat4 modelMatrix = position->getMatrix() * rotation->getMatrix() * scale->getMatrix();

    glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelMatrix)));

    shaderProgram->use();
    shaderProgram->setUniforms(modelMatrix, viewMatrix, projectionMatrix);
    shaderProgram->setNormalMatrix(normalMatrix);

}