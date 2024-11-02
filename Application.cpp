#include "Application.h"
#include "ShaderLoader.h"
#include <iostream>

Application::Application(int width, int height, const char* title)
    : camera(glm::vec3(0.0f, 1.5f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f)
{
    if (!initGLFW()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    if (!initGLEW()) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return;
    }

    glEnable(GL_DEPTH_TEST);

    initScene();

    controller = new Controller(camera, scenes, window);
    glfwSetWindowUserPointer(window, controller);

    glfwSetCursorPosCallback(window, Controller::mouse_callback);
}

bool Application::initGLFW() {
    return glfwInit();
}

bool Application::initGLEW() {
    glewExperimental = GL_TRUE;
    return glewInit() == GLEW_OK;
}

void Application::loadShaderProgram(const std::string& vertexFile, const std::string& fragmentFile) {
    ShaderProgram* shaderProgram = new ShaderProgram(vertexFile.c_str(), fragmentFile.c_str());
    camera.addObserver(shaderProgram);
    shaderPrograms.push_back(shaderProgram);
}

void Application::createScene(void (Scene::* initFunc)()) {
    Scene* scene = new Scene(shaderPrograms, camera, 800, 600);
    (scene->*initFunc)(); 
    scenes.push_back(scene);
}

void Application::initScene() {
    loadShaderProgram("default.vert", "default.frag");
    loadShaderProgram("default.vert", "colorShader2.frag");
    loadShaderProgram("default.vert", "colorShader1.frag");
    loadShaderProgram("tree.vert", "tree.frag");
    loadShaderProgram("vertexPhong.vert", "fragmentPhong.frag");
    loadShaderProgram("vertexLambert.vert", "fragmentLambert.frag");
    loadShaderProgram("vertexConstant.vert", "fragmentConstant.frag");
    loadShaderProgram("vertexBlinnPhong.vert", "fragmentBlinnPhong.frag");

    createScene(&Scene::initializeScene1);
    createScene(&Scene::initializeScene2);
    createScene(&Scene::initializeScene3);
    createScene(&Scene::initializeScene4);
}

void Application::run() {
    float lastFrameTime = 0.0f;

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        float currentFrameTime = glfwGetTime();
        float deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        controller->processInput(deltaTime); 
        controller->handleSceneSwitching(); 

        scenes[controller->getCurrentSceneIndex()]->render(camera);  

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    cleanup();
}

// Application.cpp
void Application::cleanup() {
    for (auto& scene : scenes) {
        scene->clearObjects();
        delete scene;
    }
    scenes.clear();

    for (auto& shaderProgram : shaderPrograms) {
        delete shaderProgram;
    }
    shaderPrograms.clear();

    delete controller;

    glfwTerminate();
}

Application::~Application() {
    cleanup();
}


