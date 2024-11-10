#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include <memory>  
#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"
#include "CompositeTransformation.h"
#include "Light.h"

class DrawableObject {
public:
    DrawableObject(std::shared_ptr<Model> model, std::shared_ptr<ShaderProgram> shaderProgram);
    ~DrawableObject() = default;
    void setTransformation(std::shared_ptr<CompositeTransformation> transformation);
    std::shared_ptr<CompositeTransformation> getTransformation() const;
    void draw();
    std::shared_ptr<ShaderProgram> getShaderProgram() const;

    void setupUniformsL(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const glm::vec3& cameraPosition, const Light& light);
    void setupUniforms(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const glm::vec3& cameraPosition, const std::vector<std::shared_ptr<Light>>& lights);

private:
    std::shared_ptr<Model> model;                  
    std::shared_ptr<ShaderProgram> shaderProgram;   
    std::shared_ptr<CompositeTransformation> transformation;  
};

#endif
