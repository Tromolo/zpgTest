#version 330 core
in vec3 fragNormal;
in vec3 fragPosition;

uniform vec3 lightPosition;

out vec4 fragColor;

void main() {
    vec3 lightDir = normalize(lightPosition - fragPosition);
    float diff = max(dot(fragNormal, lightDir), 0.0);
    vec4 diffuse = diff * vec4(0.385, 0.647, 0.812, 1.0);
    fragColor = vec4(0.2, 0.2, 0.2, 1.0) + diffuse;  
}
