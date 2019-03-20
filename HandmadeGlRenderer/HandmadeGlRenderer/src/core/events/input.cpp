#include "input.h"

namespace XEngine
{

    inline glm::vec2 WINInput::getMousePos(GLFWwindow* window)
    {
        double xpos, ypos;

        glfwGetCursorPos(window, &xpos, &ypos);

        glm::vec2 ret = glm::vec2(xpos, ypos);
        
        return (ret);
    }

    inline float WINInput::getMouseX(GLFWwindow* window)
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        return (float)xpos;
    }

    inline float WINInput::getMouseY(GLFWwindow* window)
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        return (float)ypos;
    }

    WINInput WINInput::setMouseButton()
    {
        return WINInput();
    }

    WINInput WINInput::setkeyboardButton()
    {
        return WINInput();
    }
    
    bool WINInput::onMouseButtonPressed(GLFWwindow* window, int key)
    {
        auto state = glfwGetMouseButton(window, key);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }
    
    bool WINInput::onKeyboardPressed(GLFWwindow *window, int key)
    {
        auto state = glfwGetKey(window, key);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }
       
    void WINInput::processInput(GLFWwindow *window, FlyCamera *cam)
    {
        //gInp.lock();
        if (onKeyboardPressed(window, GLFW_KEY_ESCAPE))
            glfwSetWindowShouldClose(window, true); 
        if (onKeyboardPressed(window, GLFW_KEY_W))
            cam->camPos += cam->speed * cam->camTarget;
        if (onKeyboardPressed(window, GLFW_KEY_S))
            cam->camPos -= cam->speed * cam->camTarget;
        if (onKeyboardPressed(window, GLFW_KEY_A))
            cam->camPos -= glm::normalize(glm::cross(cam->camTarget, cam->camUp)) * cam->speed;
        if (onKeyboardPressed(window, GLFW_KEY_D))
            cam->camPos += glm::normalize(glm::cross(cam->camTarget, cam->camUp)) * cam->speed;
        //gInp.unlock();
    }

  
}
