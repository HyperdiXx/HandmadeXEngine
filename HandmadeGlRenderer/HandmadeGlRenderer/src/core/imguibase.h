#pragma once


#ifndef GUI
#define GUI

#include <GLFW/glfw3.h>
#include "Events/events.h"


namespace XEngine
{
    namespace EngineGUI
    {
        static bool                 g_MouseJustPressed[5] = { false, false, false, false, false };
        static GLFWcursor*          g_MouseCursors[8] = { 0 };

        static GLFWmousebuttonfun   g_PrevUserCallbackMousebutton = NULL;
        static GLFWscrollfun        g_PrevUserCallbackScroll = NULL;
        static GLFWkeyfun           g_PrevUserCallbackKey = NULL;
        static GLFWcharfun          g_PrevUserCallbackChar = NULL;


        struct GraphicInterface
        {
            float locTime;
        };

        void __declspec(dllexport) InitGui(GLFWwindow* window);
        void __declspec(dllexport) UpdateGui(GLFWwindow *window, GraphicInterface *gui);
        void __declspec(dllexport) mouseUpdatePos(GLFWwindow* window);
        void __declspec(dllexport) updateMouseCursor(GLFWwindow* window);
        void __declspec(dllexport) onMouseButtonPressed(GLFWwindow* window, int button, int action, int mods);
        bool __declspec(dllexport) onMouseButtonReleased();
        bool __declspec(dllexport) onWindowResized();
        bool __declspec(dllexport) onMouseMovedEvent();
        bool __declspec(dllexport) onMouseScrolledEvent();
        bool __declspec(dllexport) onKeyboardPressed();
        bool __declspec(dllexport) onKeyboardReleased();
        void __declspec(dllexport) Shutdown();
    }
}

#endif // !GUI


