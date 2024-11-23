#version 330 core

layout(location = 0) in vec3 in_Position; // Vertex position
layout(location = 1) in vec3 in_Normal;   // Vertex normal

out vec3 fragPosition;  // Fragment position in world space
out vec3 fragNormal;    // Normal in world space

uniform mat4 model;       // Model matrix
uniform mat4 view;        // View matrix
uniform mat4 projection;  // Projection matrix
uniform mat3 normalMatrix; // Normal matrix (3x3 inverse transpose of model matrix)

void main() {
    // Transform the vertex position to world space
    fragPosition = vec3(model * vec4(in_Position, 1.0));
    
    // Transform the normal to world space
    fragNormal = normalize(normalMatrix * in_Normal);

    // Final position of the vertex in clip space
    gl_Position = projection * view * vec4(fragPosition, 1.0);
}
