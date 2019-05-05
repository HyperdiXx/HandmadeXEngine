#pragma once

#include "../shadersBase.h"
#include "../../texture.h"

namespace XEngine
{
    namespace Rendering
    {
        class Material
        {
        public:
            Material() { };
            Material(const Material& mat);

            virtual void setTexture(Texture2D *tex) = 0;
            virtual void setShader(Shader *shader) = 0;
           

        private:


        };
    }
}