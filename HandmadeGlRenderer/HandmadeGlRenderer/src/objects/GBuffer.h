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

            inline unsigned int getGBuffer() const { return gBuffer; };
            inline unsigned int getGPos() const { return gPos; };
            inline unsigned int getGNormal() const { return gNormal; };
            inline unsigned int getGColor() const { return gColor; };

        private:
            unsigned int gPos;
            unsigned int gNormal;
            unsigned int gColor;
            unsigned int gBuffer;
        };
        
    }
}
