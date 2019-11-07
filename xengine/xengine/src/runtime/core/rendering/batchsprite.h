#pragma once

#include "openglnew/irenderable2d.h"

namespace XEngine
{
    namespace Rendering
    {
        class BatchSprite : public Renderable2d
        {
        public:

            BatchSprite(float x, float y, float width, float height, glm::vec4& color);
            BatchSprite(float x, float y, float width, float height, Texture2D* text);
            ~BatchSprite()
            {

            }
        };


    }
}