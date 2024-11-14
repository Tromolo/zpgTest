#version 330 core

in vec3 Normal;   
in vec3 FragPos;  


struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
uniform Material material;


struct SpotLight {
    vec3 position;
    vec3 direction;
    vec3 color;
    float intensity;
    float cutOff;
    float outerCutOff;
};
uniform SpotLight spotlight;

struct DirectionalLight {
    vec3 direction;
    vec3 color;
    float intensity;
};
uniform DirectionalLight dirLight;

uniform vec3 viewPosition;

out vec4 FragColor;

void main()
{

    vec3 norm = normalize(Normal);

    vec3 ambient = material.ambient * dirLight.color * dirLight.intensity;

    vec3 lightDir = normalize(-dirLight.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = material.diffuse * diff * dirLight.color * dirLight.intensity;

    vec3 spotDir = normalize(spotlight.position - FragPos);
    float theta = dot(spotDir, normalize(-spotlight.direction));
    float epsilon = spotlight.cutOff - spotlight.outerCutOff;
    float intensity = clamp((theta - spotlight.outerCutOff) / epsilon, 0.0, 1.0);

    float spotDiffuse = max(dot(norm, spotDir), 0.0);
    vec3 spotlightDiffuse = material.diffuse * spotDiffuse * spotlight.color * spotlight.intensity * intensity;

    vec3 viewDir = normalize(viewPosition - FragPos);
    vec3 reflectDir = reflect(-spotDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 spotlightSpecular = material.specular * spec * spotlight.color * spotlight.intensity * intensity;

    vec3 result = ambient + diffuse + spotlightDiffuse + spotlightSpecular;
    FragColor = vec4(result, 1.0);
}
