#include "Controller.h"
#include <iostream>

Controller::Controller(Camera& camera, std::vector<Scene*>& scenes, GLFWwindow* window)
    : camera(camera), scenes(scenes), window(window), cursorVisible(true) {}


Controller::~Controller()
{
}

void Controller::processInput(float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true); 
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(CameraMovement::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(CameraMovement::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(CameraMovement::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(CameraMovement::RIGHT, deltaTime);
    processMouseInput();
}

void Controller::handleSceneSwitching() {
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !spacePressed) {
        currentSceneIndex = (currentSceneIndex + 1) % scenes.size();
        std::cout << "Switched to scene " << currentSceneIndex << std::endl;
        spacePressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
        spacePressed = false;
    }
}

void Controller::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    Controller* controller = static_cast<Controller*>(glfwGetWindowUserPointer(window));

    if (controller->firstMouse) {
        controller->lastX = xpos;
        controller->lastY = ypos;
        controller->firstMouse = false;
    }

    float xoffset = xpos - controller->lastX;
    float yoffset = controller->lastY - ypos;  

    controller->lastX = xpos;
    controller->lastY = ypos;

    controller->updateMouseMovement(xoffset, yoffset);
}

int Controller::getCurrentSceneIndex() const
{
    return currentSceneIndex;
}

void Controller::processMouseInput() {
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS && cursorVisible) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        cursorVisible = false;
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !cursorVisible) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        cursorVisible = true;
    }
}


void Controller::updateMouseMovement(float xoffset, float yoffset) {
    camera.ProcessMouseMovement(xoffset, yoffset);
}
