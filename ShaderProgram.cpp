#include "ShaderProgram.h"
#include "Light.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

ShaderProgram::ShaderProgram(const char* vertexFile, const char* fragmentFile) {
    id = loadShader(vertexFile, fragmentFile);
}

void ShaderProgram::use() const {
    glUseProgram(id);
}

void ShaderProgram::update(const glm::mat4& viewMatrix, const glm::vec3& cameraPosition)
{
    use();

    glUniformMatrix4fv(glGetUniformLocation(id, "view"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniform3fv(glGetUniformLocation(id, "viewPos"), 1, glm::value_ptr(cameraPosition));
}

void ShaderProgram::updateLight(const Light& light) {
    use();
    glUniform3fv(glGetUniformLocation(id, "lightPosition"), 1, glm::value_ptr(light.getPosition()));
    glUniform3fv(glGetUniformLocation(id, "lightColor"), 1, glm::value_ptr(light.getColor()));
    glUniform1f(glGetUniformLocation(id, "lightIntensity"), light.getIntensity());
}

void ShaderProgram::setUniforms(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) const {
    glUniformMatrix4fv(glGetUniformLocation(id, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(id, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(id, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(model)));
    glUniformMatrix3fv(glGetUniformLocation(id, "normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
}

void ShaderProgram::setNormalMatrix(const glm::mat3& normalMatrix) const
{
    glUniformMatrix3fv(glGetUniformLocation(id, "normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
}

void ShaderProgram::setVec3(const std::string& name, const glm::vec3& value) const 
{
    glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value));
}

void ShaderProgram::updateLights(const std::vector<Light*>& lights) {
    use();
    for (size_t i = 0; i < lights.size(); ++i) {
        if (lights[i]) {
            std::string base = "lights[" + std::to_string(i) + "]";
            glUniform3fv(glGetUniformLocation(id, (base + ".position").c_str()), 1, glm::value_ptr(lights[i]->getPosition()));
            glUniform3fv(glGetUniformLocation(id, (base + ".color").c_str()), 1, glm::value_ptr(lights[i]->getColor()));
            glUniform1f(glGetUniformLocation(id, (base + ".intensity").c_str()), lights[i]->getIntensity());
        }
    }

    glUniform1i(glGetUniformLocation(id, "numLights"), static_cast<int>(lights.size()));
}


ShaderProgram::~ShaderProgram() {
    deleteShader();
}
