#pragma once

#include <mutex>

#include <glm/vec2.hpp>

namespace XEngine
{
    class GLFWwindow;
    class PerspectiveCamera;

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

    void processInput(GLFWwindow* window, PerspectiveCamera *cam, bool& ui);
}