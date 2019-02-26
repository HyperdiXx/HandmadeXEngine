#pragma once

#ifndef CAMERA
#define CAMERA

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../types.h"

namespace XEngine
{
    struct Camera
    {
        glm::vec3 camPos;
        glm::vec3 camTarget;
        glm::vec3 camUp;
        real32 speed;



    };

    glm::mat4 getViewMatrix(Camera *cam);

}
#endif // !CAMERA

