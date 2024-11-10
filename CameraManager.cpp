#include "CameraManager.h"

CameraManager& CameraManager::getInstance() {
    static CameraManager instance;
    return instance;
}

Camera& CameraManager::getCameraForScene(int sceneId) {
    auto it = sceneCameras.find(sceneId);
    if (it == sceneCameras.end()) {
        auto result = sceneCameras.emplace(sceneId, Camera(glm::vec3(0.0f, 1.5f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f));
        cameraInitialized[sceneId] = false; 
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
