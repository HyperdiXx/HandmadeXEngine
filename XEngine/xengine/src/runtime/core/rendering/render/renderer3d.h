#pragma once

#include "render3d.h"
#include "../scenes/scene.h"
#include "../../cameras/camera.h"

namespace XEngine
{
    namespace Rendering
    {
        class Renderer3d
        {
        public:
            Renderer3d()
            {
                camera = new Camera();
            }
            ~Renderer3d()
            {
                delete camera;
            }

            virtual bool init() = 0;
            virtual void update() = 0;
            virtual void renderQuad() = 0;
            virtual void renderMesh() = 0;

            static void beginScene();
            static void endScene();

            static void add();

            inline Camera* getActiveCamera() { return camera; };

        protected:

            Camera* camera;

        };
    }
}
