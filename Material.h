#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>
//DRAWABLEOBJECT ? 
class Material {
public:
    // Konstruktor
    Material(const glm::vec3& ambient = glm::vec3(0.1f),
        const glm::vec3& diffuse = glm::vec3(0.8f),
        const glm::vec3& specular = glm::vec3(1.0f),
        float shininess = 32.0f);

    // Gettery
    glm::vec3 getAmbient() const;
    glm::vec3 getDiffuse() const;
    glm::vec3 getSpecular() const;
    float getShininess() const;

    // Settery
    void setAmbient(const glm::vec3& ambient);
    void setDiffuse(const glm::vec3& diffuse);
    void setSpecular(const glm::vec3& specular);
    void setShininess(float shininess);

private:
    glm::vec3 ambient;  // Koeficient ambientního osvìtlení (r_a)
    glm::vec3 diffuse;  // Koeficient difuzního osvìtlení (r_d)
    glm::vec3 specular; // Koeficient spekulárního osvìtlení (r_s)
    float shininess;    // Lesklost materiálu (pro spekulární osvìtlení)
};

#endif
