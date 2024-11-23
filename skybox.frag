#version 330 core

in vec3 fragDir;           // Direction vector from the vertex shader
out vec4 FragColor;        // Final fragment color

uniform samplerCube skybox; // Cube map sampler

void main() {
    vec3 dir = normalize(fragDir); // Normalize the direction for correct sampling
    vec3 color = texture(skybox, dir).rgb; // Sample the cube map
    FragColor = vec4(color, 1.0); // Output the color
}
