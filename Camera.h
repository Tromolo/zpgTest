#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include "ICameraObserver.h"
#include <vector>

enum class CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera {
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float Yaw;
    float Pitch;

    float MovementSpeed;
    float MouseSensitivity;
    //Camera() : Camera(glm::vec3(0.0f, 1.5f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f) {}
    Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);

    glm::mat4 GetViewMatrix();

    void ProcessKeyboard(CameraMovement direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
    void addObserver(ICameraObserver* observer);
    void removeObserver(ICameraObserver* observer);

    void setPosition(const glm::vec3& position);
    void setTarget(const glm::vec3& target);
    void setPitch(float pitch);
    void updateCameraVectors();
private:
    
    std::vector<ICameraObserver*> observers; 
    void notifyObservers();
};

#endif
