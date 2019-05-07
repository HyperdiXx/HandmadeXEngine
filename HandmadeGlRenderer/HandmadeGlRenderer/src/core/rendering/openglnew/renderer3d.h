#pragma once



#include "render3d.h"
#include "../../cameras/camera.h"

namespace XEngine
{
    namespace Rendering
    {
        class Renderer3d
        {
        public:

            virtual bool init() = 0;
            virtual void update() = 0;
            virtual void renderScene() = 0;
            virtual void renderQuad() = 0;
            virtual void renderMesh() = 0;

            inline Camera* getActive() { return camera; };

        protected:

            Camera* camera;

        };
    }
}
