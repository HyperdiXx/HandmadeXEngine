#pragma once

#include "material.h"

namespace XEngine
{
    namespace Rendering
    {
        class BPMaterial : public Material
        {
        public:
            BPMaterial() {};
            BPMaterial(Shader *shader, Texture2D *Diffuse, Texture2D* Normal, Texture2D* Spec);
            ~BPMaterial();

        private:
            Shader *mShader;
            Texture2D *mDiffuse;
            Texture2D *mNormal;
            Texture2D *mSpec;

        };
    }
}
