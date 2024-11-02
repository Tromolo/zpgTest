#include "Camera.h"

Camera::Camera(glm::vec3 position = glm::vec3(0.0f, 1.5f, 3.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f)
    : Front(glm::vec3(0.0f, 0.0f, 0.0f)), MovementSpeed(3.5f), MouseSensitivity(0.35f) {
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyboard(CameraMovement direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    if (direction == CameraMovement::FORWARD)
        Position += Front * velocity;
    if (direction == CameraMovement::BACKWARD)
        Position -= Front * velocity;
    if (direction == CameraMovement::LEFT)
        Position -= Right * velocity;
    if (direction == CameraMovement::RIGHT)
        Position += Right * velocity;

    notifyObservers();
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    if (constrainPitch) {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    updateCameraVectors();
    notifyObservers();
}

void Camera::updateCameraVectors()
{ 
    glm::vec3 front{};
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);

    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}

void Camera::addObserver(ICameraObserver* observer)
{
    observers.push_back(observer);
}

void Camera::setPitch(float pitch)
{
    Pitch = pitch;
}

void Camera::removeObserver(ICameraObserver* observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Camera::setPosition(const glm::vec3& position) {
    Position = position;
    notifyObservers();  
}

void Camera::setTarget(const glm::vec3& target) {
    Front = glm::normalize(target - Position);
    updateCameraVectors(); 
    notifyObservers();     
}

void Camera::notifyObservers() {
    glm::mat4 viewMatrix = GetViewMatrix();
    for (auto observer : observers) {
        observer->update(viewMatrix, Position); 
    }
}