#include "Controller.h"
#include <iostream>
#include "CameraManager.h"

Controller* Controller::instance = nullptr;

Controller::Controller(Camera& camera, std::vector<std::shared_ptr<Scene>>& scenes, GLFWwindow* window)
    : camera(camera), scenes(scenes), window(window), currentSceneIndex(0) {
    if (instance == nullptr) {
        instance = this; 
    }
}

Controller::~Controller() {
    if (instance == this) {
        instance = nullptr; 
    }
}

void Controller::processInput(float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true); 
    }

    int sceneId = getCurrentSceneIndex() + 1; 
    Camera& camera = CameraManager::getInstance().getCameraForScene(sceneId);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(CameraMovement::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(CameraMovement::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(CameraMovement::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(CameraMovement::RIGHT, deltaTime);

    static bool kPressed = false;
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS && !kPressed) {
        skyboxRotationEnabled = !skyboxRotationEnabled;
        kPressed = true;
        std::cout << "Skybox rotation: " << (skyboxRotationEnabled ? "Enabled" : "Disabled") << std::endl;
    }
    else if (glfwGetKey(window, GLFW_KEY_K) == GLFW_RELEASE) {
        kPressed = false;
    }
}

void Controller::handleSceneSwitching() {
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !spacePressed) {
        currentSceneIndex = (currentSceneIndex + 1) % scenes.size();
        spacePressed = true;  
    }
    else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
        spacePressed = false; 
    }
}

void Controller::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    Controller* controller = static_cast<Controller*>(glfwGetWindowUserPointer(window));
    if (controller) {
        int sceneId = controller->getCurrentSceneIndex() + 1;
        Camera& camera = CameraManager::getInstance().getCameraForScene(sceneId);

        static bool firstMouse = true;
        static float lastX = 400, lastY = 300;

        if (firstMouse) {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
            

            float xoffset = xpos - lastX;
            float yoffset = lastY - ypos;

            lastX = xpos;
            lastY = ypos;

            camera.ProcessMouseMovement(xoffset, yoffset);
        }
        else {
            firstMouse = true;
        }

        /*if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            controller->selectObjectAt(xpos, ypos);
        }*/
    }
}

Controller* Controller::getInstance() {
    return instance;
}

int Controller::getCurrentSceneIndex() const
{
    return currentSceneIndex;
}

bool Controller::isSkyboxRotationEnabled() const
{
    return skyboxRotationEnabled;
}

void Controller::updateMouseMovement(float xoffset, float yoffset) {
    camera.ProcessMouseMovement(xoffset, yoffset);
}
