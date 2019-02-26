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

        

        void InitGui(GLFWwindow* window);
        void UpdateGui(GLFWwindow *window, GraphicInterface *gui);
        void mouseUpdatePos(GLFWwindow* window);
        void updateMouseCursor(GLFWwindow* window);
        void onMouseButtonPressed(GLFWwindow* window, int button, int action, int mods);
        bool onMouseButtonReleased();
        bool onWindowResized();
        bool onMouseMovedEvent();
        bool onMouseScrolledEvent();
        bool onKeyboardPressed();
        bool onKeyboardReleased();
        void Shutdown();
    }
}

#endif // !GUI


