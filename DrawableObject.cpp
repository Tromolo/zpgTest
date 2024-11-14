#include "DrawableObject.h"
#include "Light.h"
#include <glm/gtc/type_ptr.hpp>

DrawableObject::DrawableObject(std::shared_ptr<Model> model, std::shared_ptr<ShaderProgram> shaderProgram)
    : model(std::move(model)), shaderProgram(std::move(shaderProgram)), transformation(nullptr) {}


void DrawableObject::draw(){

    if (shaderProgram) {
        shaderProgram->use();  // Ensure the shader is active
    }
    model->draw();  // Draw the model 
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

void DrawableObject::setupUniforms(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const glm::vec3& cameraPosition, const std::vector<std::shared_ptr<Light>>& lights) {
    shaderProgram->use();

    glm::mat4 modelMatrix = transformation->getMatrix();
    shaderProgram->setUniforms(modelMatrix, viewMatrix, projectionMatrix);

    glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelMatrix)));
    shaderProgram->setNormalMatrix(normalMatrix);

    if (lights.size() == 1) {
        const auto& light = lights[0];
        if (light) {
            shaderProgram->setVec3("lightPosition", light->getPosition());
            shaderProgram->setVec3("lightColor", light->getColor());
           //shaderProgram->setFloat("lightIntensity", light->getIntensity());
        }
    }
    else {
        std::vector<Light*> rawLightPointers;
        for (const auto& light : lights) {
            if (light) {
                rawLightPointers.push_back(light.get());
            }
        }
        shaderProgram->updateLights(rawLightPointers);
    }

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


