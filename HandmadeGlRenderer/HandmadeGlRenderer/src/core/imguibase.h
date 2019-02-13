#pragma once


#ifndef GUI
#define GUI

#include "Events/events.h"

namespace XEngine
{
    namespace EngineGUI
    {
        struct GraphicInterface
        {
            float locTime;
        };

        

        void InitGui();
        void UpdateGui(GraphicInterface *gui);
        bool onMouseButtonPressed();
        bool onMouseButtonReleased();
        bool onWindowResized();
        bool onMouseMovedEvent();
        bool onMouseScrolledEvent();
        bool onKeyboardPressed();
        bool onKeyboardReleased();
    }
}

#endif // !GUI


