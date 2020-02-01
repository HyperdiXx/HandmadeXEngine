#pragma once

#ifndef CONTEXT_H
#define CONTEXT_H

namespace XEngine
{
    namespace Rendering
    {
        class DeviceContext
        {
        public:
            virtual void init() = 0;
            virtual void swapBuffers() = 0;    

            static DeviceContext *create(void *win);
        };
    }
}
#endif // !CONTEXT_H

