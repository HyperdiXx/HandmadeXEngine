#pragma once

#ifndef EVENTS
#define EVENTS



namespace XEngine
{
    enum __declspec(dllexport) EventsType
    {
        MousePressed,
        MouseReleased,
        MouseMoved,
        MouseScrolled,
        KeyboardButtonPressed,
        KeyboardButtonReleased,
        WindowResized
    };


    struct __declspec(dllexport) WindowResized
    {

    };

    struct __declspec(dllexport) WindowClosed
    {

    };
    


}
#endif // !EVENTS

