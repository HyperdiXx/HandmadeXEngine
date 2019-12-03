#include "glcontext.h"

#include "opengl.h"

namespace XEngine
{
    namespace Rendering
    {
        GLContext::GLContext(GLFWwindow * window) : m_WindowHandle(window)
        {
            APIs::OpenGL::makeContext(m_WindowHandle);
            int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

            // TODO: add logs and assets

        }

        void GLContext::swapBuffers()
        {
            APIs::OpenGL::swapBuffers(m_WindowHandle);
        }
    }
}
