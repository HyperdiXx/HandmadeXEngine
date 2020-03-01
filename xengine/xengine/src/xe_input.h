#pragma once

namespace xe_input
{
    enum Button
    {
        KEYBOARD_A,
        KEYBOARD_W,
        KEYBOARD_S,
        KEYBOARD_D
    };

    void init();

    bool pressed(Button button);
}
