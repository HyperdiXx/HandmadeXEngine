#pragma once

#include "render/renderable2d.h"

namespace XEngine
{
    namespace Rendering
    {
        class Sprite : public Renderable2d
        {
        public:

            Sprite(float x, float y, float w, float h, vec4f& color, Shader& shader);  
            ~Sprite();
           

            inline const VertexBuffer* getVAO() const { return mVertexArray; };
            inline const IndexBuffer* getIBO() const { return mIndexBuffer; };
            inline Shader& getShader() const { return mShader; };
        private:
            VertexBuffer * mVertexArray;
            IndexBuffer* mIndexBuffer;
            Shader& mShader;
        };
    }
}