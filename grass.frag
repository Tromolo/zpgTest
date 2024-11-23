#version 330 core

struct PointLight {
    vec3 position;
    vec3 color;
    float intensity;
};

#define MAX_POINT_LIGHTS 4
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform int numPointLights;

uniform vec3 viewPosition;
uniform sampler2D grassTexture;

in vec3 fragPosition;
in vec3 fragNormal;  
in vec2 texCoords;  

out vec4 FragColor;

void main() {
    vec3 norm = normalize(fragNormal);                 
    vec3 viewDir = normalize(viewPosition - fragPosition); 

    vec3 ambient = vec3(0.1, 0.1, 0.1); 

    vec3 totalLight = vec3(0.0);

    for (int i = 0; i < numPointLights; i++) {
        vec3 pointLightDir = normalize(pointLights[i].position - fragPosition);

        float distance = length(pointLights[i].position - fragPosition);
        float attenuation = 1.0 / (1.0 + 0.09 * distance + 0.032 * distance * distance);

        float pointDiff = max(dot(norm, pointLightDir), 0.0);
        vec3 pointDiffuse = pointDiff * pointLights[i].color * pointLights[i].intensity * attenuation;

        vec3 pointReflectDir = reflect(-pointLightDir, norm);
        float pointSpec = pow(max(dot(viewDir, pointReflectDir), 0.0), 32.0);
        vec3 pointSpecular = pointSpec * pointLights[i].color * pointLights[i].intensity * attenuation;

        totalLight += pointDiffuse + pointSpecular;
    }

    vec3 textureColor = texture(grassTexture, texCoords).rgb;
    vec3 finalColor = ambient + totalLight;

    FragColor = vec4(finalColor * textureColor, 1.0);
}
