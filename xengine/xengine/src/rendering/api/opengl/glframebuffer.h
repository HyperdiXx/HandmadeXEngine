#pragma once

#ifndef FBO
#define FBO

#include <xenpch.h>
#include <types.h>
#include "rendering/api/base/framebuffer.h"

namespace XEngine
{
    namespace Rendering
    {
        class GLFrameBuffer : public FrameBuffer
        {
        public:
            GLFrameBuffer(int w, int h);
            ~GLFrameBuffer();

            void init();

            void bind() const;
            void unbind() const;
            void blitFramebuffer();
       
            void readPixel(int x, int y, char* data);

            void clear();

            uint32 getFbo() const { return fbo; };
            inline uint32 getWidth() const { return width; };
            inline uint32 getHeight() const { return height; };
            uint32 getColorTexture() const { return colorTexture; };
            uint32 getDepthTexture() const { return depthTexture; };

        private:
            GLFrameBuffer(const GLFrameBuffer& fr) = default;
            GLFrameBuffer(GLFrameBuffer&& fr) = default;
        private:
            uint32 fbo;
            uint32 colorTexture;
            uint32 depthTexture;
            int width, height;
        };
    }
}
#endif // !FBO

