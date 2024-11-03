#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"
#include "CompositeTransformation.h"


class DrawableObject {
public:
    DrawableObject(Model* model, ShaderProgram* shaderProgram);
    ~DrawableObject();

    void setTransformation(std::shared_ptr<CompositeTransformation> transformation);
    std::shared_ptr<CompositeTransformation> getTransformation() const;

    void draw();
    ShaderProgram* getShaderProgram() const;
    void setupUniforms(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const glm::vec3& cameraPosition, const Light& light);
    void setupUniforms(const glm::mat4& view, const glm::mat4& projection);
private:
    Model* model;
    ShaderProgram* shaderProgram;
    std::shared_ptr<CompositeTransformation> transformation;
};

#endif
