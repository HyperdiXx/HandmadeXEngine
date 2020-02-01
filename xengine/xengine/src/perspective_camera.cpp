#include "perspective_camera.h"

namespace XEngine
{
    glm::mat4 PerspectiveCamera::getProjectionMatrix()
    {      
        // @add config for cameras!
        if (!m_is_setuped)
        {
            m_projection = glm::perspective(glm::radians(45.0f), (float)1280 / (float)720, 0.1f, 1000.0f);
            m_is_setuped = true;
        }

        return m_projection;
    }

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