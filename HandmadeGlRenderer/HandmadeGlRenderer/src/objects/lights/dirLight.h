#pragma once

#include "light.h"

namespace XEngine
{
    namespace Rendering
    {
        class DirLight : public Light
        {
        public:
            DirLight(glm::vec3 p, glm::vec4 c, glm::vec3 d);

            void setDir(glm::vec3 d);

        private:

            glm::vec3 dir;
        };
    }
}
