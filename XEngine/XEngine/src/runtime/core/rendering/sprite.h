#pragma once

#include "render/irenderable2d.h"

namespace XEngine
{
    namespace Rendering
    {
        class Sprite : public Renderable2d
        {
        public:

            Sprite(float x, float y, float w, float h, glm::vec4& color, Shader& shader);  
            ~Sprite();
           

            inline const VertexArray* getVAO() const { return mvertexArray; };
            inline const IndexBuffer* getIBO() const { return mindexBuffer; };
            inline Shader& getShader() const { return mShader; };
        private:

            VertexArray * mvertexArray;
            IndexBuffer* mindexBuffer;
            Shader& mShader;
        };
    }
}