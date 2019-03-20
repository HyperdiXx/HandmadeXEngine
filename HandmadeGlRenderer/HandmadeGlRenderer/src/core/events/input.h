#pragma once

#include <mutex>

#include <GLFW/glfw3.h>

#include "../cameras/camera.h"

namespace XEngine
{
    

    struct WINInput
    {
        bool IskeyPressed;
        int key;
        float mouseX, mouseY;
    };

    static WINInput *Instance;
    //static std::mutex gInp;
    static bool IsKeyPressed(int keycode) { return Instance->IskeyPressed; };
    inline glm::vec2 getMousePos(GLFWwindow* window);
    inline float getMouseX(GLFWwindow* window);
    inline float getMouseY(GLFWwindow* window);

    WINInput setMouseButton();
    WINInput setkeyboardButton();

    bool onMouseButtonPressed(GLFWwindow* window, int key);
    bool onKeyboardPressed(GLFWwindow* window, int key);


    void processInput(GLFWwindow* window, Camera *cam);

}