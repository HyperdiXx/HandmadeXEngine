
#ifndef WIN32INPUT_CPP
#define WIN32INPUT_CPP

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
global xinput_set_state *LXInputSetState = XInputSetStateFa;
#define XInputSetState LXInputSetState

internal
bool32 initXInput()
{
    bool32 isLoaded = false;

    HMODULE xinput_lib = LoadLibrary("xinput1_4.dll");
    if (xinput_lib)
    {
        XInputGetState = (xinput_get_state*)GetProcAddress(xinput_lib, "XInputGetState");
        XInputSetState = (xinput_set_state*)GetProcAddress(xinput_lib, "XInputSetState");

        isLoaded = true;
    }   
    
    return isLoaded;
}

bool32 InputState::init(HWND wnd_handle)
{
    if (!initXInput())
    {
        print_error("Failed to init XInput!");
        return false;
    }

    #ifndef HID_USAGE_PAGE_GENERIC
    #define HID_USAGE_PAGE_GENERIC         ((USHORT) 0x01)
    #endif
    #ifndef HID_USAGE_GENERIC_MOUSE
    #define HID_USAGE_GENERIC_MOUSE        ((USHORT) 0x02)
    #endif

    RAWINPUTDEVICE rid[1] = {};
    
    rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
    rid[0].usUsage = HID_USAGE_GENERIC_MOUSE;
    rid[0].dwFlags = RIDEV_INPUTSINK;
    rid[0].hwndTarget = wnd_handle;
    
    if (!RegisterRawInputDevices(rid, 1, sizeof(rid[0])))
    {
        print_error("Failed to init Raw input devices!");
        return false;
    }
    
    return true;
}

bool32 InputState::isDown(Button button)
{
    uint8 key = (uint8)button;
    return currentKeyboardState.buttons[key] && !previousKeyboardState.buttons[key];
}

bool32 InputState::isPressed(Button button)
{   
    uint8 key = (uint8)button;
    return currentKeyboardState.buttons[key];
}

bool32 InputState::isUp(Button button)
{
    uint8 key = (uint8)button;
    return !currentKeyboardState.buttons[key] && previousKeyboardState.buttons[key];
}

void InputState::pollGamepadEvents()
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

void InputState::update()
{
    pollGamepadEvents();

    currentKeyboardState.buttons[0] = KEY_DOWN('Q');
    currentKeyboardState.buttons[1] = KEY_DOWN('W');
    currentKeyboardState.buttons[2] = KEY_DOWN('E');
    currentKeyboardState.buttons[3] = KEY_DOWN('R');
    currentKeyboardState.buttons[4] = KEY_DOWN('T');
    currentKeyboardState.buttons[5] = KEY_DOWN('Y');
    currentKeyboardState.buttons[6] = KEY_DOWN('U');
    currentKeyboardState.buttons[7] = KEY_DOWN('I');
    currentKeyboardState.buttons[8] = KEY_DOWN('O');
    currentKeyboardState.buttons[9] = KEY_DOWN('P');
    currentKeyboardState.buttons[10] = KEY_DOWN('A');
    currentKeyboardState.buttons[11] = KEY_DOWN('S');
    currentKeyboardState.buttons[12] = KEY_DOWN('D');
    currentKeyboardState.buttons[13] = KEY_DOWN('F');
    currentKeyboardState.buttons[14] = KEY_DOWN('G');
    currentKeyboardState.buttons[15] = KEY_DOWN('H');
    currentKeyboardState.buttons[16] = KEY_DOWN('J');
    currentKeyboardState.buttons[17] = KEY_DOWN('K');
    currentKeyboardState.buttons[18] = KEY_DOWN('L');
    currentKeyboardState.buttons[19] = KEY_DOWN('Z');
    currentKeyboardState.buttons[20] = KEY_DOWN('X');
    currentKeyboardState.buttons[21] = KEY_DOWN('C');
    currentKeyboardState.buttons[22] = KEY_DOWN('V');
    currentKeyboardState.buttons[23] = KEY_DOWN('B');
    currentKeyboardState.buttons[24] = KEY_DOWN('N');
    currentKeyboardState.buttons[25] = KEY_DOWN('M');



}

MouseState* InputState::getMouseState()
{
    return &currentMouseState;
}

KeyBoardState* InputState::getKeyBoardState()
{
    return &currentKeyboardState;
}

#endif
