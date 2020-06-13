#pragma pack(push, 1)

#include "xe_core.h"

namespace xe_reader_writer
{
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


    void swap_bytes(uint32* bytes)
    {
        uint32 s = (*bytes);

        *bytes = ((s << 24) | ((s & 0xFF00) << 8) | ((s >> 8) & 0xFF00) | (s >> 24));
    }

#define CONSUME(File, type) (type*)consume_size(File, sizeof(type))

    void* consume_size(xe_core::XEFile *file, uint32 size)
    {
        void* res = 0;

        if (file->size >= size)
        {
            res = file->data;
            file->data = (uint32*)file->data + size;
            file->size -= size;
        }
        else
        {
            file->size = 0;
        }

        return res;
    }

    void parse_png(xe_core::XEFile f)
    {
        printf("PNG size: %d\n", f.size);

        xe_core::XEFile *read = &f;

        png_head *pngheader = CONSUME(read, png_head);

        if (pngheader)
        {
            while (read->size > 0)
            {
                png_chunk *png_chunk_head = CONSUME(read, png_chunk);
                if (png_chunk_head)
                {
                    swap_bytes(&png_chunk_head->size);

                    switch (png_chunk_head->typeuint)
                    {
                    case FOURCC("IHDR"):
                    {
                        printf("IHDR\n");
                    } break;
                    case FOURCC("IDAT"):
                    {
                        printf("IDAT\n");
                    } break;
                    }

                    void *png_chynk_data = consume_size(read, png_chunk_head->size);
                    png_footer *png_chunk_footer = CONSUME(read, png_footer);
                    swap_bytes(&png_chunk_footer->CRC);
                }
            }
        }

        int a = 21;

    }
    
    void start_png_parser()
    {
#if 0
        if (arg_count < 2)
        {
            printf("Error: specify file name .png\n");
            return 1;
        }
#endif
        const char* read_filename = "engineassets/get.png";

        fprintf(stdout, "Loading PNG %s...\n", read_filename);

        xe_core::XEFile png_image = xe_core::readWholeFile(read_filename);

        parse_png(png_image);
    }
}
