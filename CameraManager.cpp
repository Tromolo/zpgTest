#include "CameraManager.h"

CameraManager& CameraManager::getInstance() {
    static CameraManager instance;
    return instance;
}

Camera& CameraManager::getCameraForScene(int sceneId) {
    auto it = sceneCameras.find(sceneId);
    if (it == sceneCameras.end()) {
        auto result = sceneCameras.emplace(sceneId, Camera(glm::vec3(0.0f, 1.5f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f));
        return result.first->second;
    }
    return it->second;
}

void CameraManager::updateCameraForScene(int sceneId, const glm::vec3& position, const glm::vec3& target) {
    Camera& camera = getCameraForScene(sceneId);
    camera.setPosition(position);
    camera.setTarget(target);
}
