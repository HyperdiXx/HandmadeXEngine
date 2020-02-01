#pragma once

#ifndef CAMERAH
#define CAMERAH

#include <component.h>
#include <types.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

namespace XEngine
{
    const float YAW = -90.0f;
    const float PITCH = 0.0f;
    const float SPEED = 5.0f;
    const float SENSITIVITY = 0.1f;
    const float ZOOM = 45.0f;

    class PerspectiveCamera : public Component
    {
    public:
        glm::vec3 camPos;
        glm::vec3 camTarget;
        glm::vec3 camUp;
        glm::vec3 camRight;
        glm::vec3 camWorldUp;

        real32 camYaw;
        real32 camPitch;

        real32 camMouseSensitivity;
        real32 camZoom;
        real32 speed;

        PerspectiveCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : camTarget(glm::vec3(0.0f, 0.0f, -1.0f)), speed(SPEED), camMouseSensitivity(SENSITIVITY), camZoom(ZOOM)
        {
            camPos = position;
            camWorldUp = up;
            camYaw = yaw;
            camPitch = pitch;
            updateCameraDir();
        }

        PerspectiveCamera(real32 posX, real32 posY, real32 posZ, real32 upX, real32 upY, real32 upZ, real32 yaw, real32 pitch) : camTarget(glm::vec3(0.0f, 0.0f, -1.0f)), speed(SPEED), camMouseSensitivity(SENSITIVITY), camZoom(ZOOM)
        {
            camPos = glm::vec3(posX, posY, posZ);
            camWorldUp = glm::vec3(upX, upY, upZ);
            camYaw = yaw;
            camPitch = pitch;
            updateCameraDir();
        }

        void mouseMove(real32 xoffset, real32 yoffset, real32 constrainPitch = true)
        {
            xoffset *= camMouseSensitivity;
            yoffset *= camMouseSensitivity;

            camYaw += xoffset;
            camPitch += yoffset;

            if (constrainPitch)
            {
                // @ Add clamp
                if (camPitch > 89.0f)
                    camPitch = 89.0f;
                if (camPitch < -89.0f)
                    camPitch = -89.0f;
            }

            updateCameraDir();
        }

        void mouseScroll(real32 yoffset)
        {
            if (camZoom >= 1.0f && camZoom <= 45.0f)
                camZoom -= yoffset;
            if (camZoom <= 1.0f)
                camZoom = 1.0f;
            if (camZoom >= 45.0f)
                camZoom = 45.0f;
        }

        glm::mat4 getProjectionMatrix();
        glm::mat4 getViewMatrix();
        
        inline const float getSpeed() const { return speed; };
    private:
        bool32 m_is_setuped = false;
        glm::mat4 m_projection = glm::mat4(1.0f);
        void updateCameraDir();
    };
#endif
}




