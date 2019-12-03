#pragma once

#include "render3d.h"

#include "../scenes/scene.h"

namespace XEngine
{
    namespace Rendering
    {
        class ForwardRender : public Render3D
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
