#pragma once

#ifndef GL_H
#define GL_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace APIs
{
    class OpenGL
    {
    public:
        static void clearColor(float r, float g, float b, float a)
        {
            glClearColor(r, g, b, a);
        }

        static void makeContext(GLFWwindow *m_window)
        {
            glfwMakeContextCurrent(m_window);
        }

        static void bindBuffer()
        {
            //glBindBuffer();
        }

        static void swapBuffers(GLFWwindow *m_window)
        {
            glfwSwapBuffers(m_window);
        }

        static void bindTexture(int id)
        {
            glActiveTexture(id);
        }
    };
}
#endif // !GL

