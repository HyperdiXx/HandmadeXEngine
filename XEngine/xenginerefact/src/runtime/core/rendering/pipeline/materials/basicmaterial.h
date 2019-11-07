#pragma once


#include "material.h"

namespace XEngine
{
    namespace Rendering
    {
        class BasicMaterial : public Material
        {
        public:
            BasicMaterial(Shader* shd);
            BasicMaterial(Shader* shd, Texture2D* tex);

            void setTexture(Texture2D *tex);
            void setShader(Shader *shader);

            inline Shader* getShader() { return mShader; };
            inline Texture2D* getTexture2D() { return mTexture; };
            inline uint32 getId() const { return id; };

        private:
            uint32 id;
            Shader *mShader;
            Texture2D *mTexture;
        };
    }
}
