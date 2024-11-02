#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "ShaderLoader.h"
#include "ICameraObserver.h"
#include "LightObserver.h"

class ShaderProgram :public ShaderLoader ,public ICameraObserver, public LightObserver {
public:
    
    ShaderProgram(const char* vertexFile, const char* fragmentFile);
    ~ShaderProgram();

    void use() const;

    void update(const glm::mat4& viewMatrix, const glm::vec3& cameraPosition) override;
    void updateLight(const Light& light) override;
    void setUniforms(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) const;
    void setNormalMatrix(const glm::mat3& normalMatrix) const;
    void setVec3(const std::string& name, const glm::vec3& value) const;
private:
    GLuint id;
};

#endif
