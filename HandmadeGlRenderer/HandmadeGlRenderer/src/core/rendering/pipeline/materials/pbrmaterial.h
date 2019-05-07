#pragma once

#include "material.h"


namespace XEngine
{
    namespace Rendering
    {
        class PBRMaterial : public Material
        {
        public:
            PBRMaterial() {};
            PBRMaterial(Shader* pbrShader, Texture2D *diffuse, Texture2D* normal, Texture2D *spec, Texture2D *roug);
            ~PBRMaterial();

            
            void setTextureDiffuse(Texture2D *tex);
            void setTextureNormal(Texture2D *tex);
            void setTextureSpecular(Texture2D *tex);
            void setTextureRough(Texture2D *tex);
            void setTextureAO(Texture2D *tex);

            void setShader(Shader *shader);

            inline const uint32  getId() { return id; };
            inline Shader* getShader() { return mShader; }
            inline Texture2D* getDiffuse() { return mDiffuse; }
            inline Texture2D* getNormal() { return mNormal; }
            inline Texture2D* getSpecular() { return mSpecular; }
            inline Texture2D* getRougness() { return mRoughness; }
            inline Texture2D* getAO() { return mAO; }

        private:
            uint32 id;
            Shader *mShader;
            Texture2D *mDiffuse;
            Texture2D *mNormal;
            Texture2D *mSpecular;
            Texture2D *mRoughness;
            Texture2D *mAO;
        };
    }
}
