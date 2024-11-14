#version 330 core

// Inputs from vertex shader
in vec3 worldNormal;
in vec3 worldPosition;

// Outputs
out vec4 FragColor;

// Uniforms for camera
uniform vec3 viewPosition;

// Spotlight uniforms
uniform vec3 spotlightPosition;
uniform vec3 spotlightDirection;
uniform vec3 spotlightColor;
uniform float spotlightIntensity;
uniform float spotlightCutOff;
uniform float spotlightOuterCutOff;

// Directional light uniforms
uniform vec3 directionalLightDirection;
uniform vec3 directionalLightColor;
uniform float directionalLightIntensity;

void main() {
    vec3 normal = normalize(worldNormal);

    // Directional Light Calculations
    vec3 dirLightDir = normalize(-directionalLightDirection);
    float dirDiff = max(dot(normal, dirLightDir), 0.0);
    vec3 dirDiffuse = dirDiff * directionalLightColor * directionalLightIntensity;

    // Spotlight Calculations
    vec3 spotLightDir = normalize(spotlightPosition - worldPosition);
    float theta = dot(spotLightDir, normalize(-spotlightDirection));
    float epsilon = spotlightCutOff - spotlightOuterCutOff;
    float spotlightEffect = clamp((theta - spotlightOuterCutOff) / epsilon, 0.0, 1.0);

    float spotDiff = max(dot(normal, spotLightDir), 0.0);
    vec3 spotDiffuse = spotlightEffect * spotlightColor * spotlightIntensity * spotDiff;

    // Combine Lighting
    vec3 finalColor = dirDiffuse + spotDiffuse;

    // Add ambient component
    vec3 ambient = vec3(0.05, 0.05, 0.05); // Dark ambient light
    finalColor += ambient;

    FragColor = vec4(finalColor, 1.0);
}
