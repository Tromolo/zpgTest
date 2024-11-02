#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "DrawableObject.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "Light.h"

class Scene {
public:
    Scene(const std::vector<ShaderProgram*>& shaderPrograms, Camera& cam, int width, int height);
    ~Scene();
    void initializeScene1();
    void initializeScene2();
    void initializeScene3();
    void initializeScene4();
    void render(Camera& camera);
    void clearObjects();
private:
    std::vector<DrawableObject*> objects;
    const std::vector<ShaderProgram*>& shaderPrograms;
    std::vector<Light*> lightSources;

    Camera& camera;
    int width;
    int height;
};

#endif 
