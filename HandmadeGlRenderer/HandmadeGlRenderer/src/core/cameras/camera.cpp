#include "camera.h"

namespace XEngine
{

    glm::mat4 Camera::getViewMatrix()
    {
        return glm::lookAt(camPos, camPos + camTarget, camUp);
    }
    glm::vec3 Camera::getCamPos()
    {
        return (camPos);
    }
    glm::vec3 Camera::getCamTarget()
    {
        return (camTarget);
    }
    glm::vec3 Camera::getCamUp()
    {
        return (camUp);
    }
    real32 Camera::getSpeed()
    {
        return (speed);
    }
}