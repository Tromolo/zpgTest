#version 330 core

struct PointLight {
    vec3 position;
    vec3 color;
    float intensity;
};

struct Material {
    float shininess;
};

#define MAX_POINT_LIGHTS 4
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform int numPointLights;
uniform vec3 viewPos;
uniform Material material;

in vec3 fragPosition;
in vec3 fragNormal;

out vec4 FragColor;

void main() {
    vec3 norm = normalize(fragNormal);
    vec3 normalColor = norm * 0.5 + 0.5;
    vec3 viewDir = normalize(viewPos - fragPosition);

    vec3 result = normalColor * 0.05;

    for (int i = 0; i < numPointLights; i++) {
        vec3 lightDir = normalize(pointLights[i].position - fragPosition);

        float distance = length(pointLights[i].position - fragPosition);
        float attenuation = 1.0 / (1.0 + 0.045 * distance + 0.0075 * distance * distance);

        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * pointLights[i].color * pointLights[i].intensity * attenuation;

        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = spec * pointLights[i].color * pointLights[i].intensity * attenuation;

        float proximityFactor = clamp(1.0 - (distance / 10.0), 0.0, 1.0);
        vec3 lightContribution = (diffuse + specular) * proximityFactor;

        result += lightContribution; 
    }

    FragColor = vec4(result, 1.0);
}
