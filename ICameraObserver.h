#ifndef ICAMERAOBSERVER_H
#define ICAMERAOBSERVER_H

#include <glm/glm.hpp>


class ICameraObserver {
public:
    virtual ~ICameraObserver() = default;
    virtual void update(const glm::mat4& viewMatrix, const glm::vec3& cameraPosition) = 0;
};

#endif
