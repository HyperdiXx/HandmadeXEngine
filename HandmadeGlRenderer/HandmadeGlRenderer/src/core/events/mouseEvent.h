#pragma once


namespace XEngine
{
    namespace Input
    {
        struct MouseEvent
        {
            float mouseX, mouseY;
        };


        constexpr inline float getX(MouseEvent* mouse) { return mouse->mouseX; };
        constexpr inline float getY(MouseEvent* mouse) { return mouse->mouseY; };

        struct MouseScrollEvent
        {
            float offsetX, offsetY;
        };

        constexpr inline float getOffsetX(MouseScrollEvent *m) { m->offsetX; };
        constexpr inline float getOffsetY(MouseScrollEvent* m) { m->offsetY; };
    }
}
