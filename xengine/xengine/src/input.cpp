#include "input.h"

#include <perspective_camera.h>

namespace XEngine
{
    // @Rewrite: No GLFW lib
    inline glm::vec2 getMousePos(GLFWwindow* window)
    {
        double xpos, ypos;

        //glfwGetCursorPos(window, &xpos, &ypos);

        glm::vec2 ret = glm::vec2(xpos, ypos);
        
        return (ret);
    }

    inline float getMouseX(GLFWwindow* window)
    {
        double xpos, ypos;
        //glfwGetCursorPos(window, &xpos, &ypos);
        return (float)xpos;
    }

    inline float getMouseY(GLFWwindow* window)
    {
        double xpos, ypos;
        //glfwGetCursorPos(window, &xpos, &ypos);
        return (float)ypos;
    }

    WINInput setMouseButton()
    {
        return WINInput();
    }

    WINInput setkeyboardButton()
    {
        return WINInput();
    }
    
    bool onMouseButtonPressed(GLFWwindow* window, int key)
    {
        //auto state = glfwGetMouseButton(window, key);
        //return state == GLFW_PRESS || state == GLFW_REPEAT;
        return false;
    }
    
    bool onKeyboardPressed(GLFWwindow *window, int key)
    {
        //auto state = glfwGetKey(window, key);
        //return state == GLFW_PRESS || state == GLFW_REPEAT;
        return false;
    }

    bool onKeyboardReleased(GLFWwindow *window, int key)
    {
        //auto state = glfwGetKey(window, key);
        //return state == GLFW_RELEASE;
        return false;
    }

    void processInput(GLFWwindow *window, PerspectiveCamera *cam, bool& ui)
    {
        //gInp.lock();
        /*if (onKeyboardPressed(window, GLFW_KEY_U))
        {
            ui = !ui;
        }
            
        if (onKeyboardPressed(window, GLFW_KEY_ESCAPE))
            glfwSetWindowShouldClose(window, true); 
        if (onKeyboardPressed(window, GLFW_KEY_W))
            cam->camPos += cam->speed * cam->camTarget;
        if (onKeyboardPressed(window, GLFW_KEY_S))
            cam->camPos -= cam->speed * cam->camTarget;
        if (onKeyboardPressed(window, GLFW_KEY_A))
            cam->camPos -= glm::normalize(glm::cross(cam->camTarget, cam->camUp)) * cam->speed;
        if (onKeyboardPressed(window, GLFW_KEY_D))
            cam->camPos += glm::normalize(glm::cross(cam->camTarget, cam->camUp)) * cam->speed;*/
        //gInp.unlock();
    }

  
}
