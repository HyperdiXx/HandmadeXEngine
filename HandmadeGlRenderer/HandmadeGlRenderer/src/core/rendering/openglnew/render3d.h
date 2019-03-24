#pragma once


namespace XEngine
{
    namespace Rendering
    {
        class Render3d
        {
        protected:
            virtual void sumbit() = 0;
            virtual void flush() = 0;
        };
    }
}
