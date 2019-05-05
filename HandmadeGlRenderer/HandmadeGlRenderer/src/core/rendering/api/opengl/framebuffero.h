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
            ~FrameBuffer();

            void init();

            void bind() const;
            void unbind() const;
            void blitFramebuffer();
       
            void clear();

            uint32 getFbo() const { return fbo; };
            uint32 getWidth() const { return width; };
            uint32 getHeight() const { return height; };
            uint32 getColorTexture() const { return colorTexture; };
            uint32 getDepthTexture() const { return depthTexture; };
         
            void createShadows();
        private:

            FrameBuffer(const FrameBuffer& fr) = default;
            FrameBuffer(FrameBuffer&& fr) = default;
        private:
            uint32 fbo;
            uint32 colorTexture;
            uint32 depthTexture;
            int width, height;
        };

    }
    

}



#endif // !FBO

