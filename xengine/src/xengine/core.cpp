
#ifdef PLATFORM_WINDOWS

#define STB_IMAGE_IMPLEMENTATION
#include "external\stb_image.h"
    
#endif 

namespace xe_core
{
    internal 
    XEFile readWholeFile(const char *file_name)
    {
        XEFile res = {};

        FILE *op = fopen(file_name, "rb");

        if (op)
        {
            fseek(op, 0, SEEK_END);
            res.size = ftell(op);
            fseek(op, 0, SEEK_SET);

            res.data = malloc(res.size + 1);
            fread(res.data, res.size, 1, op);
            fclose(op);
        }
        else
        {
            printf("ERROR: Cant open file %s!\n", file_name);
        }

        return res;
    }

    internal char* readFileToChar(const char *file_name)
    {
        char *result = 0;
        FILE *op = fopen(file_name, "rb");

        if (op)
        {
            fseek(op, 0, SEEK_END);
            size_t size = ftell(op);
            fseek(op, 0, SEEK_SET);

            result = (char*)malloc(size + 1);
            fread(result, size, 1, op);
            fclose(op);
        }
        else
        {
            printf("ERROR: Cant open file %s!\n", file_name);
        }

        return result;
    }

    internal 
    std::string readFileToString(const char *file_path)
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

    internal 
    unsigned char *loadTextureFromDisc(const char *path, int32 &width, int32 &height, int32 &channels, int32 flag, bool32 flip)
    {
        stbi_set_flip_vertically_on_load(flip);
        stbi_uc* image = stbi_load(path, &width, &height, &channels, flag);
        return image;
    }

    internal 
    real32 *loadTextureFloatFromDisc(const char *path, int32 &width, int32 &height, int32 &channels, int32 flag, bool32 flip)
    {
        stbi_set_flip_vertically_on_load(flip);
        real32 *image = stbi_loadf(path, &width, &height, &channels, flag);
        return image;
    }

    // Used to free stbi textures data
    internal void deleteData(void *data)
    {
        if (data != nullptr)
        {
            stbi_image_free(data);
        }
    }
}
