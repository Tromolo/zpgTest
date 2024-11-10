#version 330 core

struct Light {
    vec3 position;
    vec3 color;
    float intensity;
};

#define MAX_LIGHTS 4
uniform Light lights[MAX_LIGHTS];
uniform int numLights;
uniform vec3 viewPos;

in vec3 FragPos;
in vec3 Normal;
in vec3 VertexColor;

out vec4 FragColor;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 result = vec3(0.0);

    for (int i = 0; i < numLights; i++) {
        vec3 lightDir = normalize(lights[i].position - FragPos);

        float distance = length(lights[i].position - FragPos);
        float attenuation = 1.0 / (1.0 + 0.09 * distance + 0.032 * distance * distance);

        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lights[i].color * lights[i].intensity * attenuation;

        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
        vec3 specular = spec * lights[i].color * lights[i].intensity * attenuation;

        result += diffuse + specular;
    }

    vec3 ambient = 0.05 * VertexColor;

    vec3 finalColor = ambient + result;

    FragColor = vec4(finalColor, 1.0);
}
