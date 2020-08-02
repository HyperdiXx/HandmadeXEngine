#pragma once

#ifndef XE_IMAGE_H
#define XE_IMAGE_H

#include <xe_types.h>
#include <xenpch.h>

namespace xe_image
{
    enum FormatType
    {
        None,
        PNG,
        BMP
    };

    class Image
    {
    public:
        enum class ImageType
        {
            Image2D,
            Image3D,
            ImageHDR
        };
    public:

        Image() = default;
        Image(const std::string &path);
        Image(const char* path);
        ~Image();

        void setFormat(FormatType type);

        void setWidth(uint32 width);
        void setHeight(uint32 height);

        inline const uint32 getWidth() const { return width; };
        inline const uint32 getHeight() const { return height; };
    private:
        uint32 width = 0;
        uint32 height = 0;
        FormatType format_type;
        ImageType image_type = ImageType::Image2D;
    };
}

#endif // !XE_IMAGE_H

