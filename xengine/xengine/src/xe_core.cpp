#include "xe_core.h"

#include "xe_platform.h"

#include <stdio.h>
#include <fstream>

#ifdef PLATFORM_WINDOWS

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>
    
#endif 

namespace xe_core
{
    file read_whole_file(const char *file_name)
    {
        file res = {};

        FILE *op = fopen(file_name, "rb");

        if (op)
        {
            fseek(op, 0, SEEK_END);
            res.size = ftell(op);
            fseek(op, 0, SEEK_SET);

            res.data = malloc(res.size);
            fread(res.data, res.size, 1, op);
            fclose(op);
        }
        else
        {
            printf("ERROR: Cant open file %s!\n", file_name);
        }

        return res;
    }

    std::string read_file_string(const char *file_path)
    {
        std::ifstream file(file_path);
        if (file.fail() || !file.is_open())
        {
            printf("Failed to open file: %s\n!!!", file_path);
            return "";
        }

        std::string source;
        std::string line;

        while (getline(file, line))
        {
            source.append(line + '\n');
        }

        return source;
    }

    unsigned char *load_texture_from_disc(const char *path, int &width, int &height, int &channels, int flag, bool32 flip)
    {
        stbi_set_flip_vertically_on_load(flip);
        stbi_uc* image = stbi_load(path, &width, &height, &channels, flag);
        return image;
    }

    float *load_texturef_from_disc(const char * path, int & width, int & height, int & channels, int flag, bool32 flip)
    {
        stbi_set_flip_vertically_on_load(flip);
        real32 *image = stbi_loadf(path, &width, &height, &channels, flag);
        return image;
    }

    void delete_data(void *data)
    {
        if(data != nullptr)
            stbi_image_free(data);
    }
}
