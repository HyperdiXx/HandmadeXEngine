#pragma once

#ifndef GL_CONTEXT_H
#define GL_CONTEXT_H

#include <runtime/core/rendering/api/base/context.h>

struct GLFWwindow;

namespace XEngine
{
    namespace Rendering
    {
        class GLDeviceContext : public DeviceContext
        {
        public:

            GLDeviceContext(GLFWwindow* window);
            
            virtual void init() override;
            virtual void swapBuffers() override;

        private:
            GLFWwindow* m_window_handle;
        };
    }
}
#endif // !GL_CONTERXT_H

