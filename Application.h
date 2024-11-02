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

    ~Application();

    void run();  

private:
    void initializeScene(int sceneId);
    void loadShaderProgram(const std::string& vertexFile, const std::string& fragmentFile);
    void createScene(int sceneId ,const std::function<void(Scene&)>& initFunc);
    GLFWwindow* window;
    Camera camera;
    std::vector<Scene*> scenes;
    std::vector<ShaderProgram*> shaderPrograms;
    std::vector<Light*> lightSources;
    Controller* controller;

    bool initGLFW();
    bool initGLEW();
    void initScene();
    void cleanup();
};

#endif
