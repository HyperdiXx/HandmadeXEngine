#pragma once

#ifndef INPUT_H
#define INPUT_H

#ifdef PLATFORM_WINDOWS
    #include <windows.h>
#endif

enum class Button
{
    KEYBOARD_Q,
    KEYBOARD_W,
    KEYBOARD_E,
    KEYBOARD_R,
    KEYBOARD_T,
    KEYBOARD_Y,
    KEYBOARD_U,
    KEYBOARD_I,
    KEYBOARD_O,
    KEYBOARD_P,
    KEYBOARD_A,
    KEYBOARD_S,
    KEYBOARD_D,
    KEYBOARD_F,
    KEYBOARD_G,
    KEYBOARD_H,
    KEYBOARD_J,
    KEYBOARD_K,
    KEYBOARD_L,
    KEYBOARD_Z,
    KEYBOARD_X,
    KEYBOARD_C,
    KEYBOARD_V,
    KEYBOARD_B,
    KEYBOARD_N,
    KEYBOARD_M,

    GAMEPAD_A,
    GAMEPAD_B,
    GAMEPAD_X,
    GAMEPAD_Y
};

enum class ButtonState
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
    struct Vec2i
    {
        uint32 x, y;

        Vec2i() { }
        Vec2i(uint32 x_v, uint32 y_v) : x(x_v), y(y_v) {}
    };

    Vec2i position = Vec2i(0, 0);
    Vec2i dtPosition = Vec2i(0, 0);
    real32 wheel = 0;
    bool32 isLeftButtonPressed = false;
    bool32 isRightButtonPressed = false;
};

struct KeyBoardState
{
    bool32 buttons[256] = {};
};

class InputState
{
public:

    bool32 init(HWND wnd_handle);

    bool32 isPressed(Button button);
    bool32 isDown(Button button);
    bool32 isUp(Button button);

    void pollGamepadEvents();
    void update();

    MouseState *getMouseState();
    KeyBoardState *getKeyBoardState();

private:
    
    MouseState currentMouseState = {};
    MouseState prevMouseState = {};
    KeyBoardState currentKeyboardState = {};
    KeyBoardState previousKeyboardState = {};

    ButtonState inputMouseState = {};
    ButtonState inputKeyboardState = {};
};
#endif // !INPUT_H
