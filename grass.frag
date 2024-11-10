#version 330 core
in vec3 fragColor; // Color from vertex shader
out vec4 finalColor;

void main() {
    finalColor = vec4(fragColor, 1.0); // Output the interpolated color
}
