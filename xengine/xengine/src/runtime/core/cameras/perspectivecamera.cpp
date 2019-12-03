#include "perspectivecamera.h"

namespace XEngine
{
        glm::mat4 PerspectiveCamera::getViewMatrix()
        {
            return glm::lookAt(camPos, camPos + camTarget, camUp);
        }

        void PerspectiveCamera::updateCameraDir()
        {
            glm::vec3 front;
            front.x = cos(glm::radians(camYaw)) * cos(glm::radians(camPitch));
            front.y = sin(glm::radians(camPitch));
            front.z = sin(glm::radians(camYaw)) * cos(glm::radians(camPitch));
            camTarget = glm::normalize(front);
            camRight = glm::normalize(glm::cross(camTarget, camWorldUp));
            camUp = glm::normalize(glm::cross(camRight, camTarget));
        }
}