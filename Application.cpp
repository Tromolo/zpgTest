#include "Application.h"
#include "ShaderLoader.h"
#include <iostream>
#include "Scene1Initializer.h"
#include "Scene2Initializer.h"
#include "Scene3Initializer.h"
#include "Scene4Initializer.h" 
#include "CameraManager.h"

Application::Application(int width, int height, const char* title)
    : camera(glm::vec3(0.0f, 1.5f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f)
{
    if (!initGLFW()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

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

    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    initScene();

    controller = new Controller(camera, scenes, window);
    glfwSetWindowUserPointer(window, controller);

    glfwSetCursorPosCallback(window, Controller::mouse_callback);
}

void Application::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (app) {
        app->onWindowResized(width, height); 
    }
}

bool Application::initGLFW() {
    return glfwInit();
}

bool Application::initGLEW() {
    glewExperimental = GL_TRUE;
    return glewInit() == GLEW_OK;
}

void Application::onWindowResized(int width, int height) {
    glViewport(0, 0, width, height);

    float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    CameraManager::getInstance().updateProjectionMatrixForAllCameras(aspectRatio);
}

void Application::initializeScene(int sceneId) {
    Camera& camera = CameraManager::getInstance().getCameraForScene(sceneId);

    if (!CameraManager::getInstance().isCameraInitialized(sceneId)) {
        switch (sceneId) {
        case 1:
            camera.setPosition(glm::vec3(0.0f, 0.0f, 2.0f));  
            camera.setTarget(glm::vec3(0.0f, 0.0f, 0.0f));    
            break;
        case 2:
            camera.setPosition(glm::vec3(5.0f, 3.0f, 0.0f));
            break;
        case 3:
            camera.setPosition(glm::vec3(0.0f, 10.0f, 0.0f));
            camera.setTarget(glm::vec3(0.0f, 0.0f, 0.0f));
            camera.Pitch = -90.0f;
            camera.Yaw = 0.0f;
            camera.updateCameraVectors(); 
            break;
        case 4:
            camera.setPosition(glm::vec3(0.0f, 10.0f, 0.0f));
            camera.setTarget(glm::vec3(0.0f, 0.0f, 0.0f));
            camera.Pitch = -90.0f;
            camera.Yaw = 0.0f;
            camera.updateCameraVectors();
            break;
        default:
            camera.setPosition(glm::vec3(0.0f, 10.0f, 0.0f));
            camera.setTarget(glm::vec3(0.0f, 0.0f, 0.0f));
            break;
        }

        CameraManager::getInstance().setCameraInitialized(sceneId);
    }
}


void Application::loadShaderProgram(const std::string& vertexFile, const std::string& fragmentFile) {
    auto shaderProgram = std::make_shared<ShaderProgram>(vertexFile.c_str(), fragmentFile.c_str());
    camera.addObserver(shaderProgram);  
    shaderPrograms.push_back(shaderProgram); 
}


void Application::createScene(int sceneId, const std::function<void(Scene&, std::shared_ptr<SceneInitializer>&)>& initFunc) {
    Camera& sceneCamera = CameraManager::getInstance().getCameraForScene(sceneId);
    auto scene = std::make_shared<Scene>(shaderPrograms, sceneCamera, 800, 600);
    std::shared_ptr<SceneInitializer> initializer;
    initFunc(*scene, initializer);

    if (!initializer) {
        std::cerr << "Error: SceneInitializer not created for Scene ID: " << sceneId << std::endl;
        return;
    }

    scene->initialize(initializer);
    scenes.push_back(scene);
}

void Application::initScene() {
    loadShaderProgram("default.vert", "colorShader2.frag");
    loadShaderProgram("default.vert", "colorShader1.frag");
    loadShaderProgram("tree.vert", "tree.frag");
    loadShaderProgram("vertexPhong.vert", "fragmentPhong.frag");
    loadShaderProgram("vertexLambert.vert", "fragmentLambert.frag");
    loadShaderProgram("vertexConstant.vert", "fragmentConstant.frag");
    loadShaderProgram("vertexBlinnPhong.vert", "fragmentBlinnPhong.frag");
    loadShaderProgram("grass.vert", "grass.frag");

    createScene(1, [this](Scene& scene, std::shared_ptr<SceneInitializer>& initializer) {
        initializer = std::make_shared<Scene1Initializer>(shaderPrograms[0]); 
        scene.initialize(initializer);
        });

    createScene(2, [this](Scene& scene, std::shared_ptr<SceneInitializer>& initializer) {
        initializer = std::make_shared<Scene2Initializer>(std::vector<std::shared_ptr<ShaderProgram>>{
            shaderPrograms[2], shaderPrograms[7]
        });
        scene.initialize(initializer);
        });

    createScene(3, [this](Scene& scene, std::shared_ptr<SceneInitializer>& initializer) {
        initializer = std::make_shared<Scene3Initializer>(shaderPrograms[3]);
        scene.initialize(initializer);
        });

    createScene(4, [this](Scene& scene, std::shared_ptr<SceneInitializer>& initializer) {
        initializer = std::make_shared<Scene4Initializer>(std::vector<std::shared_ptr<ShaderProgram>>{
            shaderPrograms[3], shaderPrograms[4], shaderPrograms[5], shaderPrograms[6]
        });
        scene.initialize(initializer);
        });

    std::cout << "Total scenes loaded: " << scenes.size() << std::endl;
}


void Application::run() {
    float lastFrameTime = 0.0f;
    int lastSceneIndex = -1;
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        float currentFrameTime = glfwGetTime();
        float deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        controller->processInput(deltaTime);
        controller->handleSceneSwitching();

        int currentSceneIndex = controller->getCurrentSceneIndex();
        if (currentSceneIndex != lastSceneIndex) {
            initializeScene(currentSceneIndex + 1); 
            lastSceneIndex = currentSceneIndex;
        }

        Camera& currentCamera = CameraManager::getInstance().getCameraForScene(currentSceneIndex + 1);

        scenes[currentSceneIndex]->update(deltaTime);
        scenes[currentSceneIndex]->render(currentCamera);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    cleanup();
}

void Application::cleanup() {
    if (controller) { 
        delete controller;
        controller = nullptr;
    }

    glfwTerminate();
}

Application::~Application() {
    cleanup();
}


