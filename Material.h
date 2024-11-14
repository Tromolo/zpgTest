#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>

class Material {
public:
    Material(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float shininess);

    glm::vec3 getAmbient() const;
    glm::vec3 getDiffuse() const;
    glm::vec3 getSpecular() const;
    float getShininess() const;

private:
    glm::vec3 ambient;   // Coefficient r_a
    glm::vec3 diffuse;   // Coefficient r_d
    glm::vec3 specular;  // Coefficient r_s
    float shininess;     // Shininess for specular highlight
};

#endif
