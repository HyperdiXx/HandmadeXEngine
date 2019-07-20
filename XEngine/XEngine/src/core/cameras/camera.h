#pragma once

#ifndef CAMERAH
#define CAMERAH

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../ecs/component.h"
#include <vector>
#include "../types.h"

namespace XEngine
{

        enum Camera_Movement {
            FORWARD,
            BACKWARD,
            LEFT,
            RIGHT
        };

        const float YAW = -90.0f;
        const float PITCH = 0.0f;
        const float SPEED = 5.0f;
        const float SENSITIVITY = 0.1f;
        const float ZOOM = 45.0f;

        class Camera : public Component
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

            Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : camTarget(glm::vec3(0.0f, 0.0f, -1.0f)), speed(SPEED), camMouseSensitivity(SENSITIVITY), camZoom(ZOOM)
            {
                camPos = position;
                camWorldUp = up;
                camYaw = yaw;
                camPitch = pitch;
                updateCameraDir();
            }


            Camera(real32 posX, real32 posY, real32 posZ, real32 upX, real32 upY, real32 upZ, real32 yaw, real32 pitch) : camTarget(glm::vec3(0.0f, 0.0f, -1.0f)), speed(SPEED), camMouseSensitivity(SENSITIVITY), camZoom(ZOOM)
            {
                camPos = glm::vec3(posX, posY, posZ);
                camWorldUp = glm::vec3(upX, upY, upZ);
                camYaw = yaw;
                camPitch = pitch;
                updateCameraDir();
            }

            glm::mat4 getViewMatrix();

            void mouseMove(real32 xoffset, real32 yoffset, real32 constrainPitch = true)
            {
                xoffset *= camMouseSensitivity;
                yoffset *= camMouseSensitivity;

                camYaw += xoffset;
                camPitch += yoffset;

                if (constrainPitch)
                {
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

            inline const float getSpeed() const { return speed; };


        private:

            void updateCameraDir();
        };
    /*class Camera
    {
    public:
        Camera()
        {
            camPos = glm::vec3(0.0f, 2.0f, 10.0f);
            camTarget = glm::vec3(0.0f, 0.0f, -1.0f);
            camUp = glm::vec3(0.0f, 1.0f, 0.0f);
        }
        ~Camera()
        {

        }

        void setSpeed(real32 spe) { speed = spe; };

        glm::mat4 getViewMatrix();
        glm::vec3 getCamPos();
        glm::vec3 getCamTarget();
        glm::vec3 getCamUp();
        real32 getSpeed();
        glm::vec3 camPos;
        glm::vec3 camTarget;
        glm::vec3 camUp;
        real32 speed;
    private:
        
    };
*/
   

#endif
}




