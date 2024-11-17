#version 330 core

layout(location = 0) in vec3 in_Position; 
layout(location = 1) in vec3 in_Color;
layout(location = 2) in vec3 in_Normal;   

out vec3 fragPosition;  
out vec3 fragNormal;
out vec3 vertexColor;    

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMatrix;

void main() {
    fragPosition = vec3(model * vec4(in_Position, 1.0));
    fragNormal = normalize(normalMatrix * in_Normal);
    vertexColor = in_Color; 

    gl_Position = projection * view * vec4(fragPosition, 1.0);
}
