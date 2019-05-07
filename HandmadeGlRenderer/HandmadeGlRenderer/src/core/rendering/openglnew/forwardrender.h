#pragma once

#include "renderer3d.h"

namespace XEngine
{
    namespace Rendering
    {
        class ForwardRendering : public Renderer3d
        {
        public:
            ForwardRendering() {};

            bool init();
            void update();
            void renderScene();
            void renderMesh();
            void renderQuad();

        private:

             
        };
    }
}
