#pragma once

#include <mutex>


#include "../cameras/camera.h"


namespace XEngine
{
    
    class __declspec(dllexport) WINInput
    {
    public:

        //static bool IsKeyPressed(int keycode) { return Instance->IskeyPressed; };
        inline glm::vec2 getMousePos(GLFWwindow* window);
        inline float getMouseX(GLFWwindow* window);
        inline float getMouseY(GLFWwindow* window);

        WINInput setMouseButton();
        WINInput setkeyboardButton();

        static bool onMouseButtonPressed(GLFWwindow* window, int key);
        static bool onKeyboardPressed(GLFWwindow* window, int key);


        static void processInput(GLFWwindow* window, FlyCamera *cam);

        bool IskeyPressed;
        int key;
        float mouseX, mouseY;
    };
    static WINInput *Instance = nullptr;
    //static std::mutex gInp;
    

}