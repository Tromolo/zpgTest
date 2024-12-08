#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include <unordered_map>
#include <glm/glm.hpp>
#include "Camera.h"

class CameraManager {
public:
    static CameraManager& getInstance();

    Camera& getCameraForScene(int sceneId);

    void updateProjectionMatrixForAllCameras(float aspectRatio);
private:
    CameraManager() = default;
    CameraManager(const CameraManager&) = delete;
    CameraManager& operator=(const CameraManager&) = delete;

    std::unordered_map<int, Camera> sceneCameras;        
    std::unordered_map<int, bool> cameraInitialized;  
};

#endif
