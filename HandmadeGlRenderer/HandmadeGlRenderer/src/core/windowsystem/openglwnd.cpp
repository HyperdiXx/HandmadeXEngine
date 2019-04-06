#include "openglwnd.h"
#include "../utility/log.h"

namespace XEngine
{
    namespace Rendering
    {
        

        void WindowGL::initGL()
        {
            LOG("XEngine v.0.0.1\n");

            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_SAMPLES, 4);

            m_window = glfwCreateWindow(m_w, m_h, m_name, NULL, NULL);
            if (m_window == NULL)
            {
                std::cout << "Failed to create GLFW window" << std::endl;
                glfwTerminate();
                return;
            }
            glfwMakeContextCurrent(m_window);
            glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);
            //glfwSetCursorPosCallback(m_window, mouseCallback);
            //glfwSetScrollCallback(m_window, scrollCallback);
            setVSYNC(false);
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                std::cout << "Failed to initialize GLAD" << std::endl;
                return;
            }
            LOGSTRING("Render API : OpenGL", glGetString(GL_VERSION));
            LOGSTRING("Manufacturer: ", glGetString(GL_VENDOR));
            LOGSTRING("GLSL: ", glGetString(GL_SHADING_LANGUAGE_VERSION));
            LOGSTRING("GPU: ", glGetString(GL_RENDERER));
            LOG("Engine init\n");
            
        }

        void WindowGL::initStats()
        {
            setDepth();
            setBlendFunc();
            enableMultisample();
            
        }

        void WindowGL::setDepth()
        {
            glEnable(GL_DEPTH_TEST);
        }

        void WindowGL::setCullface()
        {
            glEnable(GL_CULL_FACE);
        }

        void WindowGL::setBlendFunc()
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }

        void WindowGL::enableMultisample()
        {
            glEnable(GL_MULTISAMPLE);
        }

        void WindowGL::setVSYNC(bool set)
        {
            if (set)
                glfwSwapInterval(1);
            else
                glfwSwapInterval(0);
        }


        void WindowGL::update() const
        {
            GLenum errors = glGetError();

            if (errors != GL_NO_ERROR)
                std::cout << "Error in " << errors << "\n";

            glfwSwapBuffers(m_window);
            glfwPollEvents();
        }
        bool32 WindowGL::isClosed()
        {
            return glfwWindowShouldClose(m_window) == 1;
        }
    }
}

bool mouseStart = true;
double lastX = (float)WINDOWWIDTH / 2.0;
double lastY = (float)WINDOWHEIGHT / 2.0;

void XEngine::framebufferSizeCallback(GLFWwindow* window, int32 width, int32 height)
{
    glViewport(0, 0, width, height);
}


//void XEngine::mouseCallback(GLFWwindow* window, double xpos, double ypos)
//{
//    if (mouseStart)
//    {
//        lastX = xpos;
//        lastY = ypos;
//        mouseStart = false;
//    }
//
//    float xoffset = xpos - lastX;
//    float yoffset = lastY - ypos; 
//
//    lastX = xpos;
//    lastY = ypos;
//
//    camera.ProcessMouseMovement(xoffset, yoffset);
//
//}
//
//void XEngine::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
//{
//    camera.ProcessMouseScroll(yoffset);
//}
//
