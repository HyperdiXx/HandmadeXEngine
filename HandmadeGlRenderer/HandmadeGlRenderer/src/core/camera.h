#pragma once

#ifndef CAMERA
#define CAMERA

#include <glm/glm.hpp>
#include "types.h"

namespace XEngine
{
    struct Camera
    {
        glm::vec3 camPos;
        glm::vec3 camTarget;
        glm::vec3 camUp;
        real32 speed;
    };

}
#endif // !CAMERA

