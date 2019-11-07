#pragma once

#ifndef RECT_H
#define RECT_H

namespace Math
{
    struct Rect
    {
        //left top point, width, height
        real32 x, y, width, height;

        Rect() : x(0), y(0), width(0), height(0) {}

        Rect(real32 xVal, real32 yVal, real32 wVal, real32 hVal) : x(xVal), y(yVal), width(wVal), height(hVal) {}

        Rect(const vec2f& pos, const vec2f& size) : x(pos.x), y(pos.y), width(size.x), height(size.y) {}

        Rect(const Rect& rr) : x(rr.x), y(rr.y), width(rr.width), height(rr.height) {}
        
        inline bool operator==(const Rect& rr)
        {
            return x == rr.x && y == rr.y && width == rr.width && height == rr.height;
        }

        inline void set(real32 xVal, real32 yVal, real32 wVal, real32 hVal)
        {
            x = xVal;
            y = yVal;
            width = wVal;
            height = hVal;
        }

        inline void setPosition(real32 xVal, real32 yVal)
        {
            x = xVal;
            y = yVal;
        }

        inline void setSize(real32 wVal, real32 hVal)
        {
            width = wVal;
            height = hVal;
        }




    };
}
#endif // !RECT_H


