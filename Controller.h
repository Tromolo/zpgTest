#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Camera.h"
#include "Scene.h"
#include <GLFW/glfw3.h>
#include <vector>

class Controller {
public:
    Controller(Camera& camera, std::vector<Scene*>& scenes, GLFWwindow* window);
    ~Controller();
    void processInput(float deltaTime); 
    void handleSceneSwitching();       
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos); 
    int getCurrentSceneIndex() const;
    void processMouseInput();
private:
    Camera& camera;              
    std::vector<Scene*>& scenes; 
    GLFWwindow* window;     

    int currentSceneIndex = 0;   
    bool firstMouse = true;      
    bool spacePressed = false; 
    float lastX = 400, lastY = 300;  

    void updateMouseMovement(float xoffset, float yoffset);

    bool cursorVisible;
};

#endif