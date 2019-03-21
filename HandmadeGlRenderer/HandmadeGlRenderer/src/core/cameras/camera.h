#pragma once

#ifndef CAMERAH
#define CAMERAH

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../types.h"

namespace XEngine
{
    class Camera
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

    

}
#endif // !CAMERA
