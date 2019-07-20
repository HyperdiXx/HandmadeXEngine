#pragma once

#include "../xenpch.h"

namespace XEngine
{
    namespace Rendering
    {
        class Gbuffer
        {
        public:

            Gbuffer();
            ~Gbuffer();

            void init();

            inline unsigned int getGBuffer() const { return gBuffer; };
            inline unsigned int getGPos() const { return gPos; };
            inline unsigned int getGNormal() const { return gNormal; };
            inline unsigned int getGColor() const { return gColor; };
            inline unsigned int getDepth() const { return gDepth; };

        private:
            unsigned int gDepth;
            unsigned int gPos;
            unsigned int gNormal;
            unsigned int gColor;
            unsigned int gBuffer;
        };
        
    }
}
