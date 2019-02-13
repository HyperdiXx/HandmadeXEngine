#include "openglwnd.h"

void setVSYNC(bool set)
{
    if (set)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);
}

void InitOpenglWindow(WindowBuffer *buffer)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    buffer->window = glfwCreateWindow(WIDTH, HEIGHT, "XEngine", NULL, NULL);
    if (buffer->window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(buffer->window);
    glfwSetFramebufferSizeCallback(buffer->window, framebufferSizeCallback);
    //glfwSetCursorPosCallback(buffer->window, mousecallback);
    setVSYNC(true);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }
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
void framebufferSizeCallback(GLFWwindow* window, int32 width, int32 height)
{
    glViewport(0, 0, width, height);
}
