#pragma once

#include "renderer3d.h"

#include "../scenes/scene.h"

namespace XEngine
{
    namespace Rendering
    {
        class ForwardRender : public Renderer3d
        {
        public:
            ForwardRender() {};

            bool init();
            void update();

            void renderScene(Scene *scene);
            void renderMesh();
            void renderQuad();

        private:
             
        };
    }
}
