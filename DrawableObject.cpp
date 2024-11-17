#include "DrawableObject.h"
#include "Light.h"
#include <glm/gtc/type_ptr.hpp>
#include "SpotLight.h"
#include "DirectionalLight.h"

DrawableObject::DrawableObject(std::shared_ptr<Model> model, std::shared_ptr<ShaderProgram> shaderProgram)
    : model(std::move(model)), shaderProgram(std::move(shaderProgram)), transformation(nullptr) {}


void DrawableObject::draw(){

    if (shaderProgram) {
        shaderProgram->use();
    }
    model->draw(); 
}

std::shared_ptr<ShaderProgram> DrawableObject::getShaderProgram() const {
    return shaderProgram;
}

void DrawableObject::setTransformation(std::shared_ptr<CompositeTransformation> transformation) {
    this->transformation = transformation;
}

std::shared_ptr<CompositeTransformation> DrawableObject::getTransformation() const {
    return transformation;
}

void DrawableObject::setupUniforms(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const glm::vec3& cameraPosition) {
    shaderProgram->use();

    glm::mat4 modelMatrix = transformation->getMatrix();
    shaderProgram->setUniforms(modelMatrix, viewMatrix, projectionMatrix);

    glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelMatrix)));
    shaderProgram->setNormalMatrix(normalMatrix);

    shaderProgram->setVec3("viewPosition", cameraPosition);
}



void DrawableObject::setMaterial(std::shared_ptr<Material> material)
{
    this->material = material;
}

std::shared_ptr<Material> DrawableObject::getMaterial() const
{
    return material;
}


