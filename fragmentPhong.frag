#version 330 core

in vec3 fragNormal;
in vec3 fragPosition;

uniform vec3 lightPosition;  
uniform vec3 viewPosition;   

out vec4 fragColor;

void main() {
    vec3 norm = normalize(fragNormal);
    vec3 lightDir = normalize(lightPosition - fragPosition);
    vec3 viewDir = normalize(viewPosition - fragPosition);

    vec3 ambient = vec3(0.11, 0.11, 0.11);  

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(0.385, 0.647, 0.812);  

    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0); 
    vec3 specular = vec3(1.0) * spec;

    vec3 result = ambient + diffuse + specular;
    fragColor = vec4(result, 1.0);
}
