#pragma once



#include "../api/base/vertexbuffer.h"
#include "../api/base/vertexarray.h"
#include "../api/base/indexbuffer.h"
#include "../pipeline/shader.h"
#include "../texture.h"
#include <xenpch.h>

namespace XEngine
{
    namespace Rendering
    {
        struct VertexSt
        {
            glm::vec3 pos;
            glm::vec2 uv;
            unsigned int color;
        };

        class Renderable3d
        {
        public:


            Renderable3d(glm::vec3 pos, glm::vec2 size, glm::vec4 color) : mPos(pos), mCount(size), mColor(color)
            {

            }

            virtual ~Renderable3d()
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
           
        };
    }
}