#include "xe_input.h"

#include "xe_platform.h"

#define KEY_DOWN(key_code) (GetAsyncKeyState(key_code) < 0)
#define KEY_UP(key_code) (!KEY_DOWN(key_code))

namespace xe_input
{
    void init()
    {

    }

    bool pressed(Button button)
    {
        uint8 keycode = (uint8)button;

        switch (button)
        {
        case KEYBOARD_A:
            keycode = 0x41;
            break;
        case KEYBOARD_S:
            keycode = 0x53;
            break;
        case KEYBOARD_W:
            keycode = 0x57;
            break;
        case KEYBOARD_D:
            keycode = 0x44;
            break;
        default:
            break;
        }

        return KEY_DOWN(keycode);
    }



}
