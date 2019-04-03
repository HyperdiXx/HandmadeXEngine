#pragma once

#ifndef TEXTH
#define TEXTH

#include <ft2build.h>
#include FT_FREETYPE_H  


#include <glm/glm.hpp>

#include "texture.h"
#include "../rendering/openglnew/irenderable2d.h"

namespace XEngine
{
    namespace Rendering
    {
        class Font : public Renderable2d
        {
        public:
            Font(std::string t, glm::vec2 pos, glm::vec4 color);
            ~Font();

            void add();

        private:

            void initFreeType();
        private:

            std::string mtext;

        };
    }

}

#endif
