#pragma once

#ifndef GL_CONTEXT_H
#define GL_CONTEXT_H

#include <runtime/core/rendering/api/base/context.h>

struct GLFWwindow;

namespace XEngine
{
    namespace Rendering
    {
        class GLContext : public Context
        {
        public:

            GLContext(GLFWwindow* window);
            
            virtual void swapBuffers() override;

        private:
            GLFWwindow* m_WindowHandle;
        };
    }
}
#endif // !GL_CONTERXT_H

