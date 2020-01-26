#pragma once

#include <runtime/core/rendering/api/base/shader.h>
#include <runtime/core/rendering/api/base/texture2d.h>

namespace XEngine
{
    namespace Rendering
    {
        class BasicMaterial
        {
        public:
            BasicMaterial() {};
            BasicMaterial(Shader* shd);
            BasicMaterial(Shader* shd, Texture2D* tex);

            void set_texture2D(Texture2D *texture);
            void set_shader(Shader *shader);

            void set_int();
            void set_vec2();
            void set_vec3();
            void set_vec4();

            void set_mat3();
            void set_mat4();


            inline Shader* get_shader() { return mShader; };
            inline Texture2D* get_texture2D() { return mTexture; };
            inline uint32 get_id() const { return id; };
        private:
            uint32 id;
            Shader *mShader;
            Texture2D *mTexture;
        };
    }
}
