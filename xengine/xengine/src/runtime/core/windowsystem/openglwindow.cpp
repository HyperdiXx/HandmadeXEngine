
#include "openglwindow.h"

#include <runtime/core/utility/log.h>

#include <rendering/api/opengl/glcontext.h>

namespace XEngine
{
    GLWindow::GLWindow(const char* n, uint32 width, uint32 height) :
        m_name(n), m_width(width), m_height(height)
    {
        Log::info("XEngine init");

        bindGLFW();

        m_window = glfwCreateWindow(m_width, m_height, m_name, NULL, NULL);
        if (m_window == NULL)
        {
            Log::error("Failed to create window!!!");
            glfwTerminate();
            return;
        }

        m_context = new Rendering::GLDeviceContext(m_window);
        //glfwSetFramebufferSizeCallback(m_window, this->framebufferSizeCallback);
        
        setVSYNC(1);
    }

    GLWindow::~GLWindow()
    {
        glfwTerminate();
    }

    void GLWindow::initStats()
    {
        setDepth();
        setBlendFunc();
        enableMultisample();
        enableFramebufferSRGB();
    }

    void GLWindow::setDepth()
    {
        glEnable(GL_DEPTH_TEST);
    }

    void GLWindow::setCullface()
    {
        glEnable(GL_CULL_FACE);
    }

    void GLWindow::setBlendFunc()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void GLWindow::enableMultisample()
    {
        glEnable(GL_MULTISAMPLE);
    }

    void GLWindow::enableFramebufferSRGB()
    {
        glEnable(GL_FRAMEBUFFER_SRGB);
    }

    void GLWindow::destroy()
    {
        glfwTerminate();
    }

    void GLWindow::setVSYNC(bool set)
    {
        glfwSwapInterval(set);
    }

    void GLWindow::framebufferSizeCallback(GLFWwindow * window, int32 width, int32 height)
    {
        glViewport(0, 0, width, height);
    }

    void GLWindow::bindGLFW()
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_SAMPLES, 4);
    }

    void GLWindow::update() const
    {
        GLenum errors = glGetError();

        if (errors != GL_NO_ERROR)
            std::cout << "Error in " << errors << "\n";
                   
        glfwPollEvents();
        glfwSwapBuffers(m_window);        
    }

    bool32 GLWindow::isClosed()
    {
        return glfwWindowShouldClose(m_window);
    }
}

