#pragma once

#include "buffer.h"
#include "vertexarray.h"
#include "indexbuffer.h"
#include "../pipeline/shader.h"

#include "../../../xenpch.h" 

namespace XEngine
{
    namespace Rendering
    {
        struct Vertex
        {
            glm::vec3 pos;
            glm::vec4 color;
        };

        class Renderable2d
        {
        public:

            Renderable2d(glm::vec3 pos, glm::vec2 size, glm::vec4 color, Shader& shader) : mPos(pos), mCount(size), mColor(color), mShader(shader)
            {
                
                GLfloat vert[] = 
                {
                    0, 0, 0,
                    0, size.y, 0,
                    size.x, size.y, 0,
                    size.x, 0, 0
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

            virtual ~Renderable2d()
            {
                delete mvertexArray;
                delete mindexBuffer;
            }

        public:

            inline const VertexArray* getVAO() const { return mvertexArray; };
            inline const IndexBuffer* getIBO() const { return mindexBuffer; };

            inline const glm::vec3& getPos() const { return mPos; };
            inline const glm::vec2& getCount() const { return mCount; };
            inline const glm::vec4& getColor() const { return mColor; };
            
            inline Shader& getShader() const { return mShader; };

        protected:
            glm::vec2 mCount;
            glm::vec3 mPos;
            glm::vec4 mColor;

            VertexArray * mvertexArray;
            IndexBuffer* mindexBuffer;
            Shader& mShader;
        };
    }
}
