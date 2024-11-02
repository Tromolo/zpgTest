// Scene.h
#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include "DrawableObject.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "Light.h"
#include "Sphere.h"
#include "tree.h"
#include "gift.h"
#include "bushes.h"

class SceneInitializer;

class Scene {
public:
    Scene(const std::vector<ShaderProgram*>& shaderPrograms, Camera& cam, int width, int height);
    ~Scene();

    void initialize(SceneInitializer& initializer);

    void render(Camera& camera);

    void clearObjects();
    void addObject(DrawableObject* object);
    void addLightSource(Light* light);

    const std::vector<Light*>& getLightSources() const;
    Camera& getCamera();

private:
    std::vector<DrawableObject*> objects;
    const std::vector<ShaderProgram*>& shaderPrograms;
    std::vector<Light*> lightSources;

    Camera& camera;
    int width;
    int height;
};

#endif
