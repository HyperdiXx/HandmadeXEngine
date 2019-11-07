#pragma once

namespace XEngine
{
    namespace Input
    {
        struct Keyboard
        {
            int keyPressed;
        };

        inline int getKey(Keyboard* keyb) { return keyb->keyPressed; };
    }
    
}
