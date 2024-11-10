#version 330 core

layout(location = 0) in vec3 aPos;  
layout(location = 1) in vec3 aNormal;   
layout(location = 2) in vec3 aColor;    

out vec3 fragPosition; 
out vec3 fragNormal;   
out vec3 fragColor;     

uniform mat4 model;        
uniform mat4 view;         
uniform mat4 projection;    

void main() {

    vec4 worldPosition = model * vec4(aPos, 1.0);
    fragPosition = vec3(worldPosition);  

    fragNormal = normalize(mat3(model) * aNormal);

    fragColor = aColor;

    gl_Position = projection * view * worldPosition;
}
