#pragma once

#include <math/vec2i.h>

namespace xe_input
{
    enum Button
    {
        KEYBOARD_A,
        KEYBOARD_W,
        KEYBOARD_S,
        KEYBOARD_D,
        KEYBOARD_V,
        KEYBOARD_B,

        GAMEPAD_A,
        GAMEPAD_B,
        GAMEPAD_X,
        GAMEPAD_Y

    };

    enum State
    {
        NONE,
        UP, 
        PRESS,
        HOLD
    };
    
    struct Gamepad
    {

    };

    struct MouseState
    {
        vec2i position = vec2i(0, 0);
        vec2i dtPosition = vec2i(0, 0);
        real32 wheel = 0;
        bool32 isLeftButtonPressed = false;
        bool32 isRightButtonPressed = false;
    };

    struct KeyBoardStates
    {
        bool32 buttons[256] = {};
    };

    void init();

    bool pressed(Button button);
    
    void poll_events();

    void update();

    MouseState *getMouseState();
}
