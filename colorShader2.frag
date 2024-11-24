#version 330 core

struct SpotLight {
    vec3 position;
    vec3 direction;
    vec3 color;
    float intensity;
    float cutOff;
    float outerCutOff;
    float exponent;
};

struct DirectionalLight {
    vec3 direction;
    vec3 color;
    float intensity;
};

uniform SpotLight spotlight;
uniform DirectionalLight directionalLight;

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

    vec3 spotlightDir = normalize(spotlight.position - fragPosition);
    float theta = dot(spotlightDir, normalize(-spotlight.direction));
    float epsilon = spotlight.cutOff - spotlight.outerCutOff;
    float spotlightFactor = clamp((theta - spotlight.outerCutOff) / epsilon, 0.0, 1.0);
    spotlightFactor = pow(spotlightFactor, spotlight.exponent);

    float spotDiff = max(dot(norm, spotlightDir), 0.0);
    vec3 spotDiffuse = spotDiff * spotlight.color * spotlight.intensity * spotlightFactor;

    vec3 spotReflectDir = reflect(-spotlightDir, norm);
    float spotSpec = pow(max(dot(viewDir, spotReflectDir), 0.0), 32.0);
    vec3 spotSpecular = spotSpec * spotlight.color * spotlight.intensity * spotlightFactor;

    totalLight += spotDiffuse + spotSpecular;

    vec3 dirLightDir = normalize(-directionalLight.direction);
    float dirDiff = max(dot(norm, dirLightDir), 0.0);
    vec3 dirDiffuse = dirDiff * directionalLight.color * directionalLight.intensity;

    vec3 dirReflectDir = reflect(-dirLightDir, norm);
    float dirSpec = pow(max(dot(viewDir, dirReflectDir), 0.0), 32.0);
    vec3 dirSpecular = dirSpec * directionalLight.color * directionalLight.intensity;

    totalLight += dirDiffuse + dirSpecular;

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
