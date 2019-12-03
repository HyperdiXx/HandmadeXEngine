#pragma once

#ifndef CONTEXT_H
#define CONTEXT_H

namespace XEngine
{
    namespace Rendering
    {
        class Context
        {
        public:            
            virtual void swapBuffers() = 0;    
        };
    }
}
#endif // !CONTEXT_H

