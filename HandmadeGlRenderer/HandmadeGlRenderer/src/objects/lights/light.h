#pragma once

#include "../../xenpch.h"

namespace XEngine
{
    namespace Rendering
    {
        class Light
        {
        public:
            Light(glm::vec3 p, glm::vec4 c);

            void init();

            void setPos(glm::vec3 p);
            void setColor(glm::vec4 c);

        private:
            glm::vec3 pos;
            glm::vec4 color;
        };
    }
}
