#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include "ICameraObserver.h"
#include <vector>
#include <memory>

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
    Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);

    glm::mat4 GetViewMatrix();

    void ProcessKeyboard(CameraMovement direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
    void addObserver(const std::shared_ptr<ICameraObserver>& observer);
    void removeObserver(const std::shared_ptr<ICameraObserver>& observer);

    void setPosition(const glm::vec3& position);
    void setTarget(const glm::vec3& target);
    void setPitch(float pitch);
    void updateCameraVectors();
private:
    
    std::vector<std::shared_ptr<ICameraObserver>> observers;

    void notifyObservers();
};

#endif
