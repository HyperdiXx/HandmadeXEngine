#pragma once

#include "render3d.h"
#include "../scenes/scene.h"
#include <runtime/core/cameras/perspectivecamera.h>

namespace XEngine
{
    namespace Rendering
    {
        class Render3D
        {
        public:
            Render3D()
            {
                camera = new PerspectiveCamera();
            }
            ~Render3D()
            {
                delete camera;
            }

            virtual bool init() = 0;
            virtual void update() = 0;
            virtual void renderQuad() = 0;
            virtual void renderMesh() = 0;
           
            inline PerspectiveCamera* getActiveCamera() { return camera; };

        protected:
            PerspectiveCamera* camera;
        };
    }
}
