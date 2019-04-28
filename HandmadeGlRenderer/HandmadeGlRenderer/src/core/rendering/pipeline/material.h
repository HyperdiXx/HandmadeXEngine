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
            Material() { };

            Material(Shader* shd);
            Material(Shader* shd, Texture2D* tex);

            Material(const Material& mat);

            void setTexture(uint32 data);
            void setShader(Shader shader);
            Shader* getShader() { return mShader; };
            Texture2D* getTexture2D() { return mTexture; };
            inline uint32 getId() const { return id; };

        private:
            uint32 id;
            Shader* mShader;
            Texture2D *mTexture;

        };
    }
}