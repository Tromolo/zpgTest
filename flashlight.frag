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

struct Material {
    vec3 ambient;  
    vec3 diffuse;  
    vec3 specular; 
    float shininess; 
};

uniform SpotLight spotlight;
uniform Material material; 
uniform vec3 viewPosition; 

in vec3 fragPosition;
in vec3 fragNormal;  

out vec4 FragColor;

void main() {
    vec3 norm = normalize(fragNormal);
    vec3 viewDir = normalize(viewPosition - fragPosition); 

    vec3 normalColor = norm * 0.5 + 0.5;

    vec3 ambient = material.ambient * vec3(0.01);

    vec3 spotlightDir = normalize(spotlight.position - fragPosition);
    float theta = dot(spotlightDir, normalize(-spotlight.direction));
    float epsilon = spotlight.cutOff - spotlight.outerCutOff;
    float spotlightFactor = clamp((theta - spotlight.outerCutOff) / epsilon, 0.0, 1.0);
    spotlightFactor = pow(spotlightFactor, spotlight.exponent);

    float spotDiff = max(dot(norm, spotlightDir), 0.0);
    vec3 spotDiffuse = spotDiff * spotlight.color * spotlight.intensity * material.diffuse * spotlightFactor;

    vec3 spotReflectDir = reflect(-spotlightDir, norm);
    float spotSpec = pow(max(dot(viewDir, spotReflectDir), 0.0), material.shininess);
    vec3 spotSpecular = spotSpec * spotlight.color * spotlight.intensity * material.specular * spotlightFactor;

    vec3 lightResult = ambient + spotDiffuse + spotSpecular;

    vec3 result = mix(normalColor * 0.05, lightResult, spotlightFactor);

    FragColor = vec4(result, 1.0); 
}
