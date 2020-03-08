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
    
    struct gamepad
    {

    };

    struct mouse_keys
    {
        vec2i position = vec2i(0, 0);
        vec2i dt_position = vec2i(0, 0);
        real32 wheel = 0;
    };

    struct keyboard_buttons
    {
        bool32 buttons[256] = {};
    };

    void init();

    bool pressed(Button button);
    
    void poll_events();
}
