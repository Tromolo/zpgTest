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
    if (textureID != 0) {
        glActiveTexture(GL_TEXTURE0);

        if (isCubemap) {
            glDepthFunc(GL_LEQUAL);
            glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
            glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
            shaderProgram->setUniform("skybox", 0);      
        }
        else {
            glBindTexture(GL_TEXTURE_2D, textureID);      
            shaderProgram->setUniform("texture1", 0);
        }
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

    glm::mat4 modelMatrix = transformation ? transformation->getMatrix() : glm::mat4(1.0f);
    shaderProgram->setUniforms(modelMatrix, viewMatrix, projectionMatrix);

    glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelMatrix)));
    shaderProgram->setNormalMatrix(normalMatrix);

    shaderProgram->setVec3("viewPosition", cameraPosition);
    shaderProgram->setVec3("objectColor", glm::vec3(0.5f, 0.7f, 1.0f));
}



void DrawableObject::setMaterial(std::shared_ptr<Material> material)
{
    this->material = material;
}

std::shared_ptr<Material> DrawableObject::getMaterial() const
{
    return material;
}


void DrawableObject::setTexture(GLuint textureID, bool isCubemap) {
    this->textureID = textureID;
    this->isCubemap = isCubemap;
}


GLuint DrawableObject::getTexture() const {
    return textureID;
}