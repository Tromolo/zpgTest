#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include <unordered_map>
#include <glm/glm.hpp>
#include "Camera.h"

class CameraManager {
public:
    static CameraManager& getInstance();

    Camera& getCameraForScene(int sceneId);

    bool isCameraInitialized(int sceneId) const;
    void setCameraInitialized(int sceneId);

    void updateCameraForScene(int sceneId, const glm::vec3& position, const glm::vec3& target);
    void updateProjectionMatrixForAllCameras(float aspectRatio);
private:
    CameraManager() = default;
    CameraManager(const CameraManager&) = delete;
    CameraManager& operator=(const CameraManager&) = delete;

    std::unordered_map<int, Camera> sceneCameras;        
    std::unordered_map<int, bool> cameraInitialized;  
};

#endif
