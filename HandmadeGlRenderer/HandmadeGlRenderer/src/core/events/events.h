#pragma once

#ifndef EVENTS
#define EVENTS


namespace XEngine
{
    enum EventsType
    {
        MousePressed,
        MouseReleased,
        MouseMoved,
        MouseScrolled,
        KeyboardButtonPressed,
        KeyboardButtonReleased,
        WindowResized
    };


    struct WindowResized
    {

    };

    struct WindowClosed
    {

    };
    


}
#endif // !EVENTS

