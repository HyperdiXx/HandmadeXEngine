#pragma once

#include "openglnew/irenderable2d.h"

namespace XEngine
{
    namespace Rendering
    {
        class Sprite : public Renderable2d
        {
        public:
            Sprite(glm::vec2& pos, float w, float h, glm::vec4& color, Shader& shader) : Renderable2d(glm::vec3(pos, 0), glm::vec2(w, h), color), mShader(shader)
            {

                GLfloat vert[] =
                {
                    0, 0, 0,
                    0, h, 0,
                    w, h, 0,
                    w, 0, 0
                };

                GLfloat colors[] =
                {
                    color.x, color.y, color.z, color.w,
                    color.x, color.y, color.z, color.w,
                    color.x, color.y, color.z, color.w,
                    color.x, color.y, color.z, color.w,
                };

                GLushort ind[] =
                {
                    0, 1, 2,
                    2, 3, 0
                };

                mvertexArray = new VertexArray();
                mindexBuffer = new IndexBuffer(ind, 6);

                mvertexArray->addBuffer(new VertexBuffer(vert, 4 * 3, 3), 0);
                mvertexArray->addBuffer(new VertexBuffer(colors, 4 * 4, 4), 1);

            }
            ~Sprite()
            {
                delete mvertexArray;
                delete mindexBuffer;
            }

            inline const VertexArray* getVAO() const { return mvertexArray; };
            inline const IndexBuffer* getIBO() const { return mindexBuffer; };

        private:

            VertexArray * mvertexArray;
            IndexBuffer* mindexBuffer;
            Shader& mShader;
        };
    }
}