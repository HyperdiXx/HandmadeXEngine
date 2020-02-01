#pragma once

#ifndef WINDOWWIN_H
#define WINDOWWIN_H

#include <xenpch.h>
#include <types.h>

namespace XEngine
{
    class Window
    {
    public:
        virtual ~Window() = default;
        
        virtual uint32 getWidth() const = 0;
        virtual uint32 getHeight() const = 0;
        
        static Window* create(const char* t, const uint32 w, const uint32 height);
    
    private:
        char* title;
        uint32 width;
        uint32 height;        
    };
}

#endif // !WINDOWWIN_H

