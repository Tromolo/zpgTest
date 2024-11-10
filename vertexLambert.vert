#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;  
layout(location = 2) in vec3 aNormal;    

out vec3 fragColor;   
out vec3 fragNormal;   
out vec3 fragPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {

    fragPosition = vec3(model * vec4(aPos, 1.0));

    fragNormal = normalize(mat3(transpose(inverse(model))) * aNormal);

    fragColor = aColor;

    gl_Position = projection * view * vec4(fragPosition, 1.0);
}
