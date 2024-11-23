#include "Textures.h"
#include <SOIL.h>
#include <iostream>

// Define the static texture cache
std::unordered_map<std::string, GLuint> Textures::textureCache;

GLuint Textures::loadTexture(const std::string& filePath, bool generateMipmaps) {
    // Check if the texture is already cached
    auto it = textureCache.find(filePath);
    if (it != textureCache.end()) {
        return it->second;
    }

    // Activate texture unit 0
    glActiveTexture(GL_TEXTURE0);

    // Load the texture using SOIL
    GLuint textureID = SOIL_load_OGL_texture(
        filePath.c_str(),
        SOIL_LOAD_RGBA,         // Load the image as RGBA
        SOIL_CREATE_NEW_ID,     // Generate a new texture ID
        SOIL_FLAG_INVERT_Y      // Flip the texture vertically
    );

    // Check for errors
    if (textureID == 0) {
        std::cerr << "Failed to load texture: " << filePath << std::endl;
        std::cerr << "SOIL error: " << SOIL_last_result() << std::endl;
        return 0;
    }

    // Bind the texture to configure its parameters
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Configure texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrap horizontally
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrap vertically
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Magnification filter

    if (generateMipmaps) {
        // Generate mipmaps and set minification filter
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    }
    else {
        // Use linear filtering for minification without mipmaps
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }

    // Unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);

    // Cache the texture for future use
    textureCache[filePath] = textureID;

    return textureID;
}

GLuint Textures::getTexture(const std::string& filePath) {
    // Check if the texture is already cached
    auto it = textureCache.find(filePath);
    if (it != textureCache.end()) {
        return it->second;
    }

    // Load and cache the texture if not already cached
    return loadTexture(filePath);
}

void Textures::clear() {
    // Delete all textures in the cache
    for (const auto& pair : textureCache) {
        glDeleteTextures(1, &pair.second);
    }
    textureCache.clear();
}
