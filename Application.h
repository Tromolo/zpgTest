#ifndef APPLICATION_H
#define APPLICATION_H

#include "Controller.h"
#include "Camera.h"
#include "Scene.h"
#include <vector>
#include <GLFW/glfw3.h>
#include "Light.h"

class Application {
public:
    Application(int width, int height, const char* title);
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    ~Application();

    void run();  

private:
    void onWindowResized(int width, int height);
    void initializeScene(int sceneId);
    void loadShaderProgram(const std::string& vertexFile, const std::string& fragmentFile);
    void createScene(int sceneId, const std::function<void(Scene&, std::shared_ptr<SceneInitializer>&)>& initFunc);
    GLFWwindow* window;
    Camera camera;
    std::vector<std::shared_ptr<Scene>> scenes;
    std::vector<std::shared_ptr<ShaderProgram>> shaderPrograms;
    std::vector<Light*> lightSources;
    Controller* controller;

    bool initGLFW();
    bool initGLEW();
    void initScene();
    void cleanup();
};

#endif
