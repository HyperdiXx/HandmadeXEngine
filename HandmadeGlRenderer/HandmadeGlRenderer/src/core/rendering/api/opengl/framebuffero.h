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

            FrameBuffer(uint32 rboDepth);
            ~FrameBuffer();

            void bindFramebuffer(uint32 type, uint32 GBuffer);
            void blitFramebuffer();

         
            void createShadows();
        private:

            FrameBuffer(const FrameBuffer& fr) = default;
            FrameBuffer(FrameBuffer&& fr) = default;
        private:
            
        };

    }
    

}



#endif // !FBO

