#pragma once

#include "../api/GL/buffer.h"
#include "../api/GL/vertexarray.h"
#include "../api/GL/indexbuffer.h"
#include "../pipeline/shader.h"
#include "../texture.h"
#include <xenpch.h>

namespace XEngine
{
    namespace Rendering
    {

        class Renderable2d
        {
        public:
          
            Renderable2d(vec3f pos, vec2f size, vec4f color) : mPos(pos), mCount(size), mColor(color)
            {
               
            }

            virtual ~Renderable2d()
            {
    
            }

            
        public:

            inline const vec3f& getPos() const { return mPos; };
            inline const vec2f& getCount() const { return mCount; };
            inline const vec4f& getColor() const { return mColor; };
            inline const std::vector<vec2f>& getUV() const { return mUV; };
            //inline const GLuint getTextId() const { return mTexture == nullptr ? 0 : mTexture->getID(); };
        protected:
            vec2f mCount;
            vec3f mPos;
            vec4f mColor;
            std::vector<vec2f> mUV;
            
        };
    }
}
