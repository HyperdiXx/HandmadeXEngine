#pragma once


namespace XEngine
{
    namespace Rendering
    {
        class Gbuffer
        {
        public:

            Gbuffer();
            ~Gbuffer();

        private:
            unsigned int gPos;
            unsigned int gNormal;
            unsigned int gColor;

        };
        
    }
}
