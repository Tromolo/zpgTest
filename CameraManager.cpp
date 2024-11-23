#include "CameraManager.h"

CameraManager& CameraManager::getInstance() {
    static CameraManager instance;
    return instance;
}

Camera& CameraManager::getCameraForScene(int sceneId) {
    auto it = sceneCameras.find(sceneId);
    if (it == sceneCameras.end()) {
        Camera newCamera;
        switch (sceneId) {
        case 1:
            newCamera.setPosition(glm::vec3(0.0f, 0.0f, 2.0f));
            newCamera.setTarget(glm::vec3(0.0f, 0.0f, 0.0f));
            break;
        case 2:
            newCamera.setPosition(glm::vec3(5.0f, 3.0f, 0.0f));
            newCamera.setTarget(glm::vec3(0.0f, 3.0f, -1.0f));
            break;
        case 3:
            newCamera.setPosition(glm::vec3(0.0f, 10.0f, 0.0f));
            newCamera.setTarget(glm::vec3(0.0f, 0.0f, 0.0f));
            newCamera.Pitch = -90.0f;
            newCamera.Yaw = 0.0f;
            newCamera.updateCameraVectors();
            break;
        case 4:
            newCamera.setPosition(glm::vec3(0.0f, 10.0f, 0.0f));
            newCamera.setTarget(glm::vec3(0.0f, 0.0f, 0.0f));
            newCamera.Pitch = -90.0f;
            newCamera.Yaw = 0.0f;
            newCamera.updateCameraVectors();
            break;
        case 5:
            newCamera.setPosition(glm::vec3(5.0f, 3.0f, 0.0f));
            newCamera.Pitch = 15.0f;
            newCamera.Yaw = -90.0f;
            newCamera.updateCameraVectors();
            break;
        case 6:
            newCamera.setPosition(glm::vec3(5.0f, 3.0f, 0.0f));
            newCamera.Pitch = 15.0f;
            newCamera.Yaw = -90.0f;
            newCamera.updateCameraVectors();
            break;
        default:
            newCamera.setPosition(glm::vec3(0.0f, 0.0f, 2.0f));
            newCamera.setTarget(glm::vec3(0.0f, 0.0f, 0.0f));
        }
        auto result = sceneCameras.emplace(sceneId, std::move(newCamera));
        cameraInitialized[sceneId] = true;
        return result.first->second;
    }
    return it->second;
}



bool CameraManager::isCameraInitialized(int sceneId) const {
    auto it = cameraInitialized.find(sceneId);
    return it != cameraInitialized.end() && it->second;
}

void CameraManager::setCameraInitialized(int sceneId) {
    cameraInitialized[sceneId] = true;
}

void CameraManager::updateCameraForScene(int sceneId, const glm::vec3& position, const glm::vec3& target) {
    Camera& camera = getCameraForScene(sceneId);
    camera.setPosition(position);
    camera.setTarget(target);
}

void CameraManager::updateProjectionMatrixForAllCameras(float aspectRatio) {
    for (auto& pair : sceneCameras) {
        pair.second.setProjectionMatrix(glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f));
    }
}