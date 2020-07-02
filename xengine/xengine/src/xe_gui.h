#pragma once

#include "types.h"
#include <glm/fwd.hpp>
#include <vector>

namespace xe_gui
{
    enum ElementType
    {
        UI_BUTTON, 
        UI_WIDGET
    };

    struct UIElement
    {
        uint64 id;
        ElementType type;
        real32 x, y;
        real32 width;
        real32 height;
        const char *text;
    };
    
    struct ElementHolder
    {
        std::vector<UIElement> uiStates;
    };

    void drawUI();
    bool makeButton(uint64 id, real32 x, real32 y, real32 w, real32 h, const char* text);
    bool makeButton(real32 x, real32 y, real32 w, real32 h, const char* text);
    bool makeButton(uint64 id, real32 x, real32 y, real32 w, real32 h, const glm::vec4 &color);

    void initImguiImpl();

    void startFrame();
    void endFrame();

    void drawTopBar();

    void drawButton(const char *wo);

    void clearContext();
}
