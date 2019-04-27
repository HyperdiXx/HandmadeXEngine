#pragma once

#include "shadersBase.h"
#include "../texture.h"

namespace XEngine
{
    namespace Rendering
    {
        class Material
        {
        public:
            Material() {};
            Material(Shader* shader);
            Material(Shader* shader, Texture2D* mtext);

            Material(const Material& mat);

            void setTexture(uint32 data);
            void setShader(Shader shader);
            Shader* getShader() { return mShader; };
            inline uint32 getId() const { return id; };

        private:
            uint32 id;
            Shader* mShader;
        };
    }
}