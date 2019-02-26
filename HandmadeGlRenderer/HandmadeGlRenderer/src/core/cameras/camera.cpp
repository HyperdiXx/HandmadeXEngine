#include "camera.h"

namespace XEngine
{
    glm::mat4 getViewMatrix(Camera *cam)
    {
        return glm::lookAt(cam->camPos, cam->camPos + cam->camTarget, cam->camUp);
    }
}