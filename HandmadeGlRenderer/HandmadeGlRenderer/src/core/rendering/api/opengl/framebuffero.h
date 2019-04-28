#pragma once

#ifndef FBO
#define FBO

#include "../../../types.h"
#include "../../../../xenpch.h"

#include<unordered_map>

namespace XEngine
{
    namespace Rendering
    {
        class FrameBuffer
        {
        public:
            FrameBuffer() {};
            FrameBuffer(int w, int h);
            FrameBuffer(uint32 rboDepth);
            ~FrameBuffer();

            void init();

            void bindFramebuffer() const;
            void blitFramebuffer();

            void unbindFramebuffer() const;

            void clear();

            uint32 getFbo() const { return fbo; };
            uint32 getWidth() const { return width; };
            uint32 getHeight() const { return height; };
         
            void createShadows();
        private:

            FrameBuffer(const FrameBuffer& fr) = default;
            FrameBuffer(FrameBuffer&& fr) = default;
        private:
            uint32 fbo;
            uint32 textureFBO;
            int width, height;
        };

    }
    

}



#endif // !FBO

