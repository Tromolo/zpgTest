#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 worldPosition; // Output for fragment shader
out vec3 worldNormal;   // Output for fragment shader

void main() {
    // Transform vertex position to world space
    vec4 worldPos = model * vec4(aPos, 1.0);
    worldPosition = worldPos.xyz;

    // Transform normal to world space
    worldNormal = mat3(transpose(inverse(model))) * aNormal;

    // Final position in clip space
    gl_Position = projection * view * worldPos;
}
