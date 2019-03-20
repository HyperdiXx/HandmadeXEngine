#include "camera.h"

namespace XEngine
{

    glm::mat4 FlyCamera::getViewMatrix()
    {
        return glm::lookAt(camPos, camPos + camTarget, camUp);
    }
    glm::vec3 FlyCamera::getCamPos()
    {
        return (camPos);
    }
    glm::vec3 FlyCamera::getCamTarget()
    {
        return (camTarget);
    }
    glm::vec3 FlyCamera::getCamUp()
    {
        return (camUp);
    }
    real32 FlyCamera::getSpeed()
    {
        return (speed);
    }
}