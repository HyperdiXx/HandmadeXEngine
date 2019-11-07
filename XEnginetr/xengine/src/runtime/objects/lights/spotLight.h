#pragma once

#include "light.h"

namespace XEngine
{
    namespace Rendering
    {
        class SpotLight : public Light
        {
        public:
            SpotLight(glm::vec3 p, glm::vec4 c);
        };
    }
}
