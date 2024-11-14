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
#include <memory>
#include "Renderer.h"

class SceneInitializer;

class Scene {
public:
    Scene(const std::vector<std::shared_ptr<ShaderProgram>>& shaderPrograms, Camera& camera, int width, int height);
    ~Scene();

    void initialize(std::shared_ptr<SceneInitializer> initializer);
    std::shared_ptr<SceneInitializer> getInitializer() const;
    void render(Camera& camera);
    void update(float deltaTime);
    size_t getLightSourceCount() const;
    void clearObjects();
    void clearLightSources();
    void addObject(std::shared_ptr<DrawableObject> object);
    void addLightSource(std::shared_ptr<Light> light);

    Camera& getCamera();

private:
    Renderer renderer;
    std::vector<std::shared_ptr<DrawableObject>> objects;  
    std::vector<std::shared_ptr<Light>> lightSources;      
    std::vector<std::shared_ptr<ShaderProgram>> shaderPrograms;
    std::shared_ptr<SceneInitializer> initializer;
    Camera& camera;
    int width;
    int height;
};

#endif
