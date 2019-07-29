#pragma once


namespace Math
{
    class Rect
    {
    public:

        //left top point, width, height
        float x, y, width, height;

        Rect() : x(0), y(0), width(0), height(0) {}

        Rect(float xVal, float yVal, float wVal, float hVal) : x(xVal), y(yVal), width(wVal), height(hVal) {}

        Rect(const vec2<float>& pos, const vec2<float>& size) : x(pos.x), y(pos.y), width(size.x), height(size.y) {}

        Rect(const Rect& rr) : x(rr.x), y(rr.y), width(rr.width), height(rr.height) {}
        
        inline bool operator==(const Rect& rr)
        {
            return x == rr.x && y == rr.y && width == rr.width && height == rr.height;
        }

        inline void set(float xVal, float yVal, float wVal, float hVal)
        {
            x = xVal;
            y = yVal;
            width = wVal;
            height = hVal;
        }

        inline void setPosition(float xVal, float yVal)
        {
            x = xVal;
            y = yVal;
        }

        inline void setSize(float wVal, float hVal)
        {
            width = wVal;
            height = hVal;
        }




    };
}

   