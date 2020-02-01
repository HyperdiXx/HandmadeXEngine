#pragma pack(push, 1)

#include "types.h"

struct png_ihdr
{
    uint32 width;
    uint32 height;
    uint8 bit_depth;
    uint8 color_type;
    uint8 compression_method;
    uint8 filter_method;
    uint8 interlace_method;
};

struct png_head
{
    uint8 signature[8];
};

struct png_chunk
{
    uint32 size;
    union
    {
        char* type;
        uint32 typeuint;
    };

};

struct png_footer
{
    uint32 CRC;
};

static uint8 png_signature[] = { 137, 80, 78, 71, 13, 10, 26, 10 };

#pragma pack(pop)

#define FOURCC(string) (((uint32)(string[0]) << 0) | ((uint32)(string[1]) << 8) | ((uint32)(string[2]) << 16) | ((uint32)(string[3]) << 24))
