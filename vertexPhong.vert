#version 330 core

layout(location = 0) in vec3 aPos; 
layout(location = 1) in vec3 aNormal;   

out vec3 fragPosition;  
out vec3 fragNormal;    

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMatrix;

void main() {
    vec4 worldPosition = model * vec4(aPos, 1.0);
    fragPosition = vec3(worldPosition);    
    fragNormal = normalize(normalMatrix * aNormal); 

    gl_Position = projection * view * worldPosition;
}
