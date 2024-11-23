#version 330 core

layout(location = 0) in vec3 in_Position; // Cube vertex positions

out vec3 fragDir; // Direction vector for sampling the cube map

uniform mat4 projection; // Projection matrix
uniform mat4 view;       // View matrix (without translation)
uniform mat4 model;      // Model matrix for skybox (if rotation/scale needed)

void main() {
    fragDir = mat3(view) * mat3(model) * in_Position; // Transform direction
    gl_Position = projection * view * model * vec4(in_Position, 1.0); // Standard projection
}
