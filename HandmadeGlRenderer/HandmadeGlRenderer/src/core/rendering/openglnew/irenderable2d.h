#pragma once

#include "buffer.h"
#include "vertexarray.h"
#include "indexbuffer.h"
#include "../pipeline/shader.h"
#include "../texture.h"
#include "../../../xenpch.h" 

namespace XEngine
{
    namespace Rendering
    {
        struct Vertex
        {
            glm::vec3 pos;
            glm::vec2 uv;
            unsigned int color;
        };

        class Renderable2d
        {
        public:
            

            Renderable2d(glm::vec3 pos, glm::vec2 size, glm::vec4 color) : mPos(pos), mCount(size), mColor(color)
            {
               
            }

            virtual ~Renderable2d()
            {
    
            }

            
        public:

            inline const glm::vec3& getPos() const { return mPos; };
            inline const glm::vec2& getCount() const { return mCount; };
            inline const glm::vec4& getColor() const { return mColor; };
            inline const std::vector<glm::vec2>& getUV() const { return mUV; };
            //inline const GLuint getTextId() const { return mTexture == nullptr ? 0 : mTexture->getID(); };
        protected:
            glm::vec2 mCount;
            glm::vec3 mPos;
            glm::vec4 mColor;
            std::vector<glm::vec2> mUV;
            Texture2d* mTexture;
        };
    }
}
