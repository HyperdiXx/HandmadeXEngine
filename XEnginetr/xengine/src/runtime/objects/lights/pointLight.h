#pragma once

#include "light.h"

namespace XEngine
{
    namespace Rendering
    {
        class PointLight : public Light
        {
        public:
            PointLight(glm::vec3 p, glm::vec4 c);
        };
    }
}
