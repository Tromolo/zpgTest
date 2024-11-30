#version 330 core

in vec3 fragPos;
in vec3 normalOut;
in vec2 texCoordsOut;
out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform sampler2D texture1;
uniform vec3 viewPos;

void main() {

    vec3 texColor = texture(texture1, texCoordsOut).rgb;


    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * texColor;

    vec3 norm = normalize(normalOut);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * texColor;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
