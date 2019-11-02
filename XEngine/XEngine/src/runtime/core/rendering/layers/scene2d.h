#pragma once

#include "layer.h"

namespace XEngine
{
    namespace Rendering
    {
        class Scene2D : public Layer
        {
        public:
            Scene2D();
            ~Scene2D();

        private:
            Shader* mShader;
        };
        
    }
}
