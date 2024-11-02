#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include "Camera.h"
#include <unordered_map>

class CameraManager {
public:
    static CameraManager& getInstance();

    Camera& getCameraForScene(int sceneId);

    void updateCameraForScene(int sceneId, const glm::vec3& position, const glm::vec3& target);

private:
    CameraManager() = default;
    CameraManager(const CameraManager&) = delete;
    CameraManager& operator=(const CameraManager&) = delete;

    std::unordered_map<int, Camera> sceneCameras;
};

#endif
