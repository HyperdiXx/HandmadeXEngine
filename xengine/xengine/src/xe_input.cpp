#include "xe_input.h"

#include "xe_platform.h"
#include "xe_utility.h"

#ifdef _WIN32

#include <xinput.h>

#endif 

namespace xe_input
{
    #define KEY_DOWN(key_code) (GetAsyncKeyState(key_code) < 0)
    #define KEY_UP(key_code) (!KEY_DOWN(key_code))

    #define XINPUT_GET_STATE(name) DWORD WINAPI name(DWORD dwUserIndex, XINPUT_STATE *pState)
    typedef XINPUT_GET_STATE(xinput_get_state);
    XINPUT_GET_STATE(XInputGetStateFa)
    {
        return 0;
    }
    static xinput_get_state *LXInputGetState = XInputGetStateFa;
    #define XInputGetState LXInputGetState
    
    #define XINPUT_SET_STATE(name) DWORD WINAPI name(DWORD dwUserIndex, XINPUT_VIBRATION *pVibration) 
    typedef XINPUT_SET_STATE(xinput_set_state);
    XINPUT_SET_STATE(XInputSetStateFa)
    {
        return 0;
    }
    static xinput_set_state *LXInputSetState = XInputSetStateFa;
    #define XInputSetState LXInputSetState

    std::vector<uint8_t*> loop_mess;

    static MouseState currentMouseState = {};
    static MouseState prevMouseState = {};
    static KeyBoardStates keyboard = {};

    static State inputMouseState = {};
    static State inputKeyboardState = {};

    void init()
    {
        HMODULE xinput_lib = LoadLibrary("xinput1_4.dll");
        if (xinput_lib)
        {
            XInputGetState = (xinput_get_state*)GetProcAddress(xinput_lib, "XInputGetState");
            XInputSetState = (xinput_set_state*)GetProcAddress(xinput_lib, "XInputSetState");
        }

        loop_mess.reserve(64);

        RAWINPUTDEVICE rid[2] = {};

        // Mouse
        rid[0].usUsagePage = 0x01;
        rid[0].usUsage = 0x02;
        rid[0].dwFlags = 0;
        rid[0].hwndTarget = 0;

        // Keyboard
        rid[1].usUsagePage = 0x01;
        rid[1].usUsage = 0x06;
        rid[1].dwFlags = 0;
        rid[1].hwndTarget = 0;

        int size = sizeof(rid) / sizeof(rid[0]);

        if (RegisterRawInputDevices(rid, size, sizeof(rid[0])) == FALSE)
        {
            xe_utility::error("Failed to init RegisterRawInputDevices!");
        }

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
        case KEYBOARD_V:
            keycode = 'V';
            break;
        case KEYBOARD_B:
            keycode = 'B';
            break;
        default:
            break;
        }

        return KEY_DOWN(keycode);
    }

    void poll_events()
    {
        for (DWORD controller_index = 0;
            controller_index < XUSER_MAX_COUNT;
            ++controller_index)
        {
            XINPUT_STATE state;
            ZeroMemory(&state, sizeof(XINPUT_STATE));
            if (XInputGetState(controller_index, &state) == ERROR_SUCCESS)
            {
                XINPUT_GAMEPAD *gamepad = &state.Gamepad;
                bool32 up = (gamepad->wButtons & XINPUT_GAMEPAD_DPAD_UP);
                bool32 down = (gamepad->wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
                bool32 a = (gamepad->wButtons & XINPUT_GAMEPAD_A);
                bool32 b = (gamepad->wButtons & XINPUT_GAMEPAD_B);
                bool32 x = (gamepad->wButtons & XINPUT_GAMEPAD_X);
                bool32 y = (gamepad->wButtons & XINPUT_GAMEPAD_Y);

                if (a)
                {
                    printf("A button pressed\n");
                }

                if (b)
                {
                    printf("B button pressed\n");
                }

                if (x)
                {
                    printf("X button pressed\n");
                }

                if (y)
                {
                    printf("Y button pressed\n");
                }

            }
            else
            {
                // unavailable
            }
        }
    }

    void update()
    {
        if (prevMouseState.isLeftButtonPressed == false && currentMouseState.isLeftButtonPressed == false)
        {
            inputMouseState = State::UP;
        }

        if (prevMouseState.isLeftButtonPressed && currentMouseState.isLeftButtonPressed)
        {
            inputMouseState = State::HOLD;
        }
        
        if (prevMouseState.isLeftButtonPressed == false && currentMouseState.isLeftButtonPressed)
        {
            inputKeyboardState = State::PRESS;
        }

        prevMouseState.isLeftButtonPressed = currentMouseState.isLeftButtonPressed;
        prevMouseState.isRightButtonPressed = currentMouseState.isRightButtonPressed;

        switch (inputMouseState)
        {
        case State::PRESS:
        {

        } break;
        case State::UP:
        {
            //currentMouseState.is_left_button_pressed = false;
        } break;

        default:
            break;
        }

    }

    MouseState *getMouseState()
    {
        return &currentMouseState;
    }

}
