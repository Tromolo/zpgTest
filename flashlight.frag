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

struct PointLight {
    vec3 position;
    vec3 color;
    float intensity;
};

struct Material {
    vec3 ambient;  
    vec3 diffuse;  
    vec3 specular; 
    float shininess; 
};

#define MAX_POINT_LIGHTS 4

uniform SpotLight spotlight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform int numPointLights; 
uniform Material material; 
uniform vec3 viewPosition; 

in vec3 fragPosition;
in vec3 fragNormal;  

out vec4 FragColor;

void main() {
    vec3 norm = normalize(fragNormal);
    vec3 viewDir = normalize(viewPosition - fragPosition); 

    vec3 normalColor = norm * 0.5 + 0.5;

    vec3 ambient = material.ambient * vec3(0.1); 

    vec3 spotlightDir = normalize(spotlight.position - fragPosition);
    float theta = dot(spotlightDir, normalize(-spotlight.direction));
    float epsilon = spotlight.cutOff - spotlight.outerCutOff;
    float spotlightFactor = clamp((theta - spotlight.outerCutOff) / epsilon, 0.0, 1.0);
    spotlightFactor = pow(spotlightFactor, spotlight.exponent);

    float spotDiff = max(dot(norm, spotlightDir), 0.0);
    vec3 spotDiffuse = spotDiff * spotlight.color * spotlight.intensity * material.diffuse * spotlightFactor * 2.0; 

    vec3 spotReflectDir = reflect(-spotlightDir, norm);
    float spotSpec = pow(max(dot(viewDir, spotReflectDir), 0.0), material.shininess);
    vec3 spotSpecular = spotSpec * spotlight.color * spotlight.intensity * material.specular * spotlightFactor * 2.0; 

    vec3 spotlightResult = spotDiffuse + spotSpecular;

    vec3 pointLightResult = vec3(0.0);
    for (int i = 0; i < numPointLights; ++i) {
        vec3 pointLightDir = normalize(pointLights[i].position - fragPosition);
        
        float diff = max(dot(norm, pointLightDir), 0.0);
        vec3 diffuse = diff * pointLights[i].color * pointLights[i].intensity * material.diffuse * 1.5;

        vec3 reflectDir = reflect(-pointLightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = spec * pointLights[i].color * pointLights[i].intensity * material.specular * 1.5;

        pointLightResult += diffuse + specular;
    }

    vec3 lightResult = ambient + spotlightResult + pointLightResult;

    vec3 result = mix(normalColor * 0.05, lightResult, spotlightFactor);

    FragColor = vec4(result, 1.0); 
}
