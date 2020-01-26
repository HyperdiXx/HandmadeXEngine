#pragma once

#include "basicmaterial.h"

namespace XEngine
{
    namespace Rendering
    {
        class BPMaterial : public BasicMaterial
        {
        public:
            BPMaterial(Shader *shader, Texture2D *diffuse, Texture2D* Normal, Texture2D* Spec) {};
            ~BPMaterial();

            void set_normal_texture2D(Texture2D *texture);
            void set_specular_texture2D(Texture2D *texture);
        private:
            Texture2D *m_diffuse;
            Texture2D *m_normal;
            Texture2D *m_spec;
        };
    }
}
