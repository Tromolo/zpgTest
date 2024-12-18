#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include <memory>  
#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"
#include "CompositeTransformation.h"
#include "Light.h"
#include "Material.h"

class DrawableObject {
public:
    DrawableObject(std::shared_ptr<Model> model, std::shared_ptr<ShaderProgram> shaderProgram);
    ~DrawableObject() = default;
    void setTransformation(std::shared_ptr<CompositeTransformation> transformation);
    std::shared_ptr<CompositeTransformation> getTransformation() const;
    void draw();
    std::shared_ptr<ShaderProgram> getShaderProgram() const;

    void setupUniforms(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const glm::vec3& cameraPosition);
    void setMaterial(std::shared_ptr<Material> material);
    std::shared_ptr<Material> getMaterial() const;

    void setTexture(GLuint textureID, bool isCubemap);
    GLuint getTexture() const;

    unsigned int getID() const;
    void setID(unsigned int newID);
private:
    unsigned int id;
    std::shared_ptr<Model> model;                  
    std::shared_ptr<ShaderProgram> shaderProgram;   
    std::shared_ptr<CompositeTransformation> transformation;  
    std::shared_ptr<Material> material;
    GLuint textureID = 0;
    bool isCubemap = false;
};

#endif
