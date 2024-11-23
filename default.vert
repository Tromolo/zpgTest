#version 330 core

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Normal;
layout(location = 2) in vec2 in_TexCoords;

out vec3 fragPosition;   // Position in world space
out vec3 fragNormal;     // Normal in world space
out vec2 texCoords;      // Texture coordinates

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMatrix;

void main() {
    fragPosition = vec3(model * vec4(in_Position, 1.0));  // World space position
    fragNormal = normalize(normalMatrix * in_Normal);    // Transformed normal
    texCoords = in_TexCoords;                           // Pass texture coordinates

    gl_Position = projection * view * vec4(fragPosition, 1.0);
}
