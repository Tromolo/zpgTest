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

void Application::initializeScene(int sceneId) {
    Camera& camera = CameraManager::getInstance().getCameraForScene(sceneId);

    if (!CameraManager::getInstance().isCameraInitialized(sceneId)) {
        switch (sceneId) {
        case 1:
            camera.setPosition(glm::vec3(0.0f, 10.0f, 0.0f));
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
    ShaderProgram* shaderProgram = new ShaderProgram(vertexFile.c_str(), fragmentFile.c_str());
    camera.addObserver(shaderProgram);
    shaderPrograms.push_back(shaderProgram);
}

void Application::createScene(int sceneId, const std::function<void(Scene&)>& initFunc) {
    Camera& sceneCamera = CameraManager::getInstance().getCameraForScene(sceneId);

    Scene* scene = new Scene(shaderPrograms, sceneCamera, 800, 600);
    initFunc(*scene);
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

    createScene(1, [this](Scene& scene) {
        Scene1Initializer scene1Initializer(shaderPrograms[1]);
        scene.initialize(scene1Initializer);
        });

    createScene(2, [this](Scene& scene) {
        Scene2Initializer scene2Initializer(shaderPrograms[3]);
        scene.initialize(scene2Initializer);
        });

    createScene(3, [this](Scene& scene) {
        Scene3Initializer scene3Initializer(shaderPrograms[4]);
        scene.initialize(scene3Initializer);
        });

    std::vector<ShaderProgram*> giftShaders = { shaderPrograms[4], shaderPrograms[5], shaderPrograms[6], shaderPrograms[7] };
    createScene(4, [this, giftShaders](Scene& scene) {
        Scene4Initializer scene4Initializer(giftShaders);
        scene.initialize(scene4Initializer);
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
        scenes[currentSceneIndex]->render(currentCamera);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    cleanup();
}

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


