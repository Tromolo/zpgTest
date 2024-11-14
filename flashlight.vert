#version 330 core

layout(location = 0) in vec3 aPos;      // Vertex position
layout(location = 1) in vec3 aNormal;   // Vertex normal

out vec3 FragPos;  // Output to fragment shader
out vec3 Normal;   // Output to fragment shader

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    // Calculate the vertex position in world space
    FragPos = vec3(model * vec4(aPos, 1.0));
    
    // Transform the normal to world space and normalize it
    Normal = mat3(transpose(inverse(model))) * aNormal;
    
    // Calculate the final vertex position in clip space
    gl_Position = projection * view * vec4(FragPos, 1.0);
}
