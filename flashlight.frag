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
uniform vec3 viewPosition;

in vec3 fragPosition; 
in vec3 fragNormal;   
in vec3 vertexColor;  


out vec4 FragColor;

void main() {
    vec3 norm = normalize(fragNormal);
    vec3 viewDir = normalize(viewPosition - fragPosition);

    vec3 ambient = vec3(0.1); 

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

    vec3 dirLightDir = normalize(-directionalLight.direction); 
    float dirDiff = max(dot(norm, dirLightDir), 0.0);           
    vec3 dirDiffuse = dirDiff * directionalLight.color * directionalLight.intensity;


    vec3 dirReflectDir = reflect(-dirLightDir, norm);
    float dirSpec = pow(max(dot(viewDir, dirReflectDir), 0.0), 32.0); 
    vec3 dirSpecular = dirSpec * directionalLight.color * directionalLight.intensity;

    vec3 result = ambient + spotDiffuse + spotSpecular + dirDiffuse + dirSpecular;

    FragColor = vec4(result * vertexColor, 1.0); 
}
