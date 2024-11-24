#ifndef TEXTURES_H
#define TEXTURES_H

#include <string>
#include <unordered_map>
#include <GL/glew.h>
#include "Soil.h" 

class Textures {
public:
    static GLuint loadTexture(const std::string& filePath, bool generateMipmaps = true);
    static GLuint getTexture(const std::string& filePath);
    static void setCubemapParameters();
    static void clear();

private:
    Textures() = default;
    static std::unordered_map<std::string, GLuint> textureCache;
};

#endif 
