#include "Material.h"

// Konstruktor
Material::Material(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float shininess)
    : ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess) {}

// Gettery
glm::vec3 Material::getAmbient() const {
    return ambient;
}

glm::vec3 Material::getDiffuse() const {
    return diffuse;
}

glm::vec3 Material::getSpecular() const {
    return specular;
}

float Material::getShininess() const {
    return shininess;
}

// Settery
void Material::setAmbient(const glm::vec3& ambient) {
    this->ambient = ambient;
}

void Material::setDiffuse(const glm::vec3& diffuse) {
    this->diffuse = diffuse;
}

void Material::setSpecular(const glm::vec3& specular) {
    this->specular = specular;
}

void Material::setShininess(float shininess) {
    this->shininess = shininess;
}
