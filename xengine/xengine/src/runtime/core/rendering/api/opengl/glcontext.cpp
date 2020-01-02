#include "glcontext.h"

#include "opengl.h"

#include <GLFW/glfw3.h>

namespace XEngine
{
    namespace Rendering
    {
        GLDeviceContext::GLDeviceContext(GLFWwindow * window) : m_window_handle(window)
        {
            glfwMakeContextCurrent(m_window_handle);
            int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

            // TODO: add logs and assets
        }

        void GLDeviceContext::init()
        {

        }

        void GLDeviceContext::swapBuffers()
        {
            glfwSwapBuffers(m_window_handle);
        }
    }
}
