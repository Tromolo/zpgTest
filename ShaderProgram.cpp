#include "ShaderProgram.h"
#include "Light.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include "SpotLight.h"
#include "DirectionalLight.h"
#include "Material.h"
#include "PointLight.h"

#define MAX_POINT_LIGHTS 4

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

    if (const auto* spotlight = dynamic_cast<const SpotLight*>(&light)) {
        glUniform3fv(glGetUniformLocation(id, "spotlight.position"), 1, glm::value_ptr(spotlight->getPosition()));
        glUniform3fv(glGetUniformLocation(id, "spotlight.direction"), 1, glm::value_ptr(spotlight->getDirection()));
        glUniform3fv(glGetUniformLocation(id, "spotlight.color"), 1, glm::value_ptr(spotlight->getColor()));
        glUniform1f(glGetUniformLocation(id, "spotlight.intensity"), spotlight->getIntensity());
        glUniform1f(glGetUniformLocation(id, "spotlight.cutOff"), spotlight->getCutOff());
        glUniform1f(glGetUniformLocation(id, "spotlight.outerCutOff"), spotlight->getOuterCutOff());
        glUniform1f(glGetUniformLocation(id, "spotlight.exponent"), spotlight->getExponent());

    }
    else if (const auto* directionalLight = dynamic_cast<const DirectionalLight*>(&light)) {
        glUniform3fv(glGetUniformLocation(id, "directionallight.direction"), 1, glm::value_ptr(directionalLight->getDirection()));
        glUniform3fv(glGetUniformLocation(id, "directionallight.color"), 1, glm::value_ptr(directionalLight->getColor()));
        glUniform1f(glGetUniformLocation(id, "directionallight.intensity"), directionalLight->getIntensity());
    }
    else if (const auto* pointLight = dynamic_cast<const PointLight*>(&light)) {
        static int currentLightIndex = 0; 
        if (currentLightIndex < MAX_POINT_LIGHTS) {
            std::string baseName = "pointLights[" + std::to_string(currentLightIndex) + "].";
            glUniform3fv(glGetUniformLocation(id, (baseName + "position").c_str()), 1, glm::value_ptr(pointLight->getPosition()));
            glUniform3fv(glGetUniformLocation(id, (baseName + "color").c_str()), 1, glm::value_ptr(pointLight->getColor()));
            glUniform1f(glGetUniformLocation(id, (baseName + "intensity").c_str()), pointLight->getIntensity());
            currentLightIndex++;
        }
    }

    else {
        std::cerr << "Unknown light type passed to ShaderProgram::updateLight!" << std::endl;
    }
}



void ShaderProgram::setUniforms(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) const {
    use();
    glUniformMatrix4fv(glGetUniformLocation(id, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(id, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(id, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(model)));
    glUniformMatrix3fv(glGetUniformLocation(id, "normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
}

void ShaderProgram::setNormalMatrix(const glm::mat3& normalMatrix) const
{
    use();
    glUniformMatrix3fv(glGetUniformLocation(id, "normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
}

void ShaderProgram::setVec3(const std::string& name, const glm::vec3& value) const 
{
    use();
    glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value));
}

void ShaderProgram::setFloat(const std::string& name, float value) const {
    use();
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void ShaderProgram::updateLights(const std::vector<std::shared_ptr<Light>>& lights) {
    use();

    for (size_t i = 0; i < lights.size(); ++i) {
        if (lights[i]) {
            std::string base = "pointLights[" + std::to_string(i) + "]";
            glUniform3fv(glGetUniformLocation(id, (base + ".position").c_str()), 1, glm::value_ptr(lights[i]->getPosition()));
            glUniform3fv(glGetUniformLocation(id, (base + ".color").c_str()), 1, glm::value_ptr(lights[i]->getColor()));
            glUniform1f(glGetUniformLocation(id, (base + ".intensity").c_str()), lights[i]->getIntensity());
        }
    }
    glUniform1i(glGetUniformLocation(id, "numPointLights"), static_cast<int>(lights.size()));
}

void ShaderProgram::setUniform(const std::string& name, int value) const {
    use();
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}


void ShaderProgram::setMaterial(const Material& material) {
    use();
    glUniform3fv(glGetUniformLocation(id, "material.ambient"), 1, glm::value_ptr(material.getAmbient()));
    glUniform3fv(glGetUniformLocation(id, "material.diffuse"), 1, glm::value_ptr(material.getDiffuse()));
    glUniform3fv(glGetUniformLocation(id, "material.specular"), 1, glm::value_ptr(material.getSpecular()));
    glUniform1f(glGetUniformLocation(id, "material.shininess"), material.getShininess());
}


ShaderProgram::~ShaderProgram() {
    deleteShader();
}