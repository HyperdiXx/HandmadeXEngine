#pragma once

#include <xenpch.h>

namespace XEngine
{
    namespace Rendering
    {
        class Light
        {
        public:
            Light(glm::vec3 p, glm::vec4 c);

            void setPos(float x, float y, float z);
            void setPos(glm::vec3 p);
            void setColor(glm::vec4 c);

            inline glm::vec3 getColor() const { return color; }
            inline glm::vec3 getPos() const { return pos; }

        protected:
            glm::vec3 pos;
            glm::vec4 color;
        };
    }
}
