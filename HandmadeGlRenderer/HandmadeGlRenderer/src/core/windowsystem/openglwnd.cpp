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
            //glfwSetCursorPosCallback(buffer->window, mousecallback);
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
void framebufferSizeCallback(GLFWwindow* window, int32 width, int32 height)
{
    glViewport(0, 0, width, height);
}


#if 0
void mousecallback(GLFWwindow* window, real64 xpos, real64 ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    real32 xoffset = xpos - lastX;
    real32 yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    real32 sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;


    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    camTarget = glm::normalize(front);
}
#endif
