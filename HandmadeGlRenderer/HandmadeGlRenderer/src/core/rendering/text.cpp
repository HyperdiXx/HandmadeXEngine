#include "text.h"


namespace XEngine
{
    namespace Rendering
    {
        Font::Font(std::string t, glm::vec2 pos, glm::vec4 color) : Renderable2d(glm::vec3(pos, 0), glm::vec2(1.0f, 1.0f), color)
        {

        }
    }
}
