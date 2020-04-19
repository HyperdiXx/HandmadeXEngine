#pragma once

#ifndef XENGINE_CORE_H
#define XENGINE_CORE_H

#include "types.h"
#include <string>

namespace xe_core
{
    struct file
    {
        uint32 size;
        void *data;
    };

    file read_whole_file(const char *file_name);
    std::string read_file_string(const char *file_path);
    unsigned char* load_texture_from_disc(const char* path, int &width, int &height, int &channels, int flag, bool32 flip);
    float *load_texturef_from_disc(const char* path, int &width, int &height, int &channels, int flag, bool32 flip);
    void delete_data(void *data);
}

#endif // !XENGINE_CORE_H
