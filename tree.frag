#version 330 core

struct PointLight {
    vec3 position;  // Position of the point light
    vec3 color;     // Color of the light
    float intensity; // Light intensity
};

struct Material {
    float shininess; // Shininess exponent
};

#define MAX_POINT_LIGHTS 4
uniform PointLight pointLights[MAX_POINT_LIGHTS]; // Array of point lights
uniform int numPointLights;                      // Number of active point lights
uniform vec3 viewPos;                            // Camera/viewer position
uniform Material material;                       // Material properties

in vec3 fragPosition;  // Fragment position in world space
in vec3 fragNormal;    // Normal at the fragment position

out vec4 FragColor;

void main() {
    vec3 norm = normalize(fragNormal);           // Normalize the interpolated normal
    vec3 baseColor = abs(norm);                  // Base color derived from the normal
    vec3 viewDir = normalize(viewPos - fragPosition); // Direction to the camera

    vec3 result = baseColor * 0.2; // Base color with some ambient factor

    for (int i = 0; i < 2; i++) {
        vec3 lightDir = normalize(pointLights[i].position - fragPosition);

        // Distance-based attenuation
        float distance = length(pointLights[i].position - fragPosition);
        float attenuation = 1.0 / (1.0 + 0.045 * distance + 0.0075 * distance * distance);

        // Diffuse lighting
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * pointLights[i].color * pointLights[i].intensity * attenuation;

        // Specular lighting (Phong model)
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = spec * pointLights[i].color * pointLights[i].intensity * attenuation;

        result += diffuse + specular; // Add light contribution
    }

    FragColor = vec4(result, 1.0); // Output final fragment color
}
