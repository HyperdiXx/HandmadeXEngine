#include "openglwnd.h"
#include <stb_image.h>
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

            setVSYNC(false);
            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                std::cout << "Failed to initialize GLAD" << std::endl;
                return;
            }

            GLFWimage images[1];
            images[0].pixels = stbi_load("src/textures/logo.png", &images[0].width, &images[0].height, 0, 4);
            glfwSetWindowIcon(m_window, 1, images);
            stbi_image_free(images[0].pixels);

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

