#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include "Model.h"
#include "ShaderProgram.h"
#include "Position.h"
#include "Scale.h"
#include "Rotation.h"


class DrawableObject {
public:
    DrawableObject(Model* model, ShaderProgram* shaderProgram);
    ~DrawableObject();

    Position* getPosition() const;
    Rotation* getRotation() const;
    Scale* getScale() const;

    void draw();
    ShaderProgram* getShaderProgram() const;
    void setupUniforms(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const glm::vec3& cameraPosition, const Light& light);

    void setupUniforms(const glm::mat4& view, const glm::mat4& projection);
private:
    Model* model;
    ShaderProgram* shaderProgram;
    Position* position;
    Rotation* rotation;
    Scale* scale;
};

#endif
