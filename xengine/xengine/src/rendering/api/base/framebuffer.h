#pragma once


namespace XEngine
{
    namespace Rendering
    {
        class FrameBuffer
        {
        protected:
            virtual void init() = 0;
        public:

            virtual void bind() const = 0;
            virtual void unbind() const = 0;
            virtual void blitFramebuffer() = 0;

            virtual void readPixel() = 0;

            virtual void clear() = 0;

            virtual uint32 getWidth() const = 0;
            virtual uint32 getHeight() const = 0;
        };
    }
}