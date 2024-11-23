#version 330 core

layout(location = 0) in vec3 in_Position; // Vertex positions
layout(location = 1) in vec2 in_TexCoord; // UV coordinates

out vec2 texCoord; // Pass UV coordinates to the fragment shader

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    texCoord = in_TexCoord;
    gl_Position = projection * view * model * vec4(in_Position, 1.0);
}
