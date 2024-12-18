#include "Controller.h"
#include <iostream>
#include "CameraManager.h"
#include "Scene5Initializer.h"

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

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            controller->processMouseClick(xpos, ypos, camera, sceneId);
        }
    }
}

void Controller::processMouseClick(double xpos, double ypos, Camera& camera, int sceneId) {
    if (sceneId < 1 || sceneId > scenes.size()) {
        printf("Invalid scene ID: %d\n", sceneId);
        return;
    }

    Scene* currentScene = scenes[sceneId - 1].get();
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    float aspectRatio = static_cast<float>(viewport[2]) / static_cast<float>(viewport[3]);
    glm::mat4 viewMatrix = camera.GetViewMatrix();
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
    glm::vec4 viewportVec = glm::vec4(viewport[0], viewport[1], viewport[2], viewport[3]);

    int x = static_cast<int>(xpos);
    int y = static_cast<int>(viewport[3] - ypos);

    GLfloat depth;
    GLuint index;

    glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
    glReadPixels(x, y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

    glm::vec3 screenPos = glm::vec3(x, y, depth);
    glm::vec3 worldPos = glm::unProject(screenPos, viewMatrix, projectionMatrix, viewportVec);

    printf("Screen Pos: [%f, %f, %f]\n", screenPos.x, screenPos.y, screenPos.z);
    printf("World Pos: [%f, %f, %f]\n", worldPos.x, worldPos.y, worldPos.z);
    printf("Stencil Index: %u\n", index);

    if (index == 1) {
        printf("Index 1 detected. Spawning a tree at this position.\n");
        auto initializer = std::dynamic_pointer_cast<Scene5Initializer>(currentScene->getInitializer());
        if (initializer) {
            initializer->spawnTree(worldPos, *currentScene);
        }
    }
    else if (index != 0) {
        printf("Object with stencil ID %u was clicked. Attempting to remove it.\n", index);
        auto& objects = currentScene->getObjects();
        auto it = std::remove_if(objects.begin(), objects.end(), [index](const std::shared_ptr<DrawableObject>& obj) {
            if (obj->getID() == index) {
                printf("Removing object with ID %u from the scene.\n", index);
                return true;
            }
            return false;
            });

        if (it != objects.end()) {
            objects.erase(it, objects.end());
            printf("Object with ID %u has been removed.\n", index);
        }
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
