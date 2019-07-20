#pragma once

#include <deque>
#include "render2d.h"
#include "../sprite.h"

namespace XEngine
{
    namespace Rendering
    {
        class Renderer2d : public Render2d
        {
        public:

            void submit(const Renderable2d* renderObj) override;
            void flush() override;

        private:
            std::deque<const Sprite *> mrenderQ;
        };
    }
}