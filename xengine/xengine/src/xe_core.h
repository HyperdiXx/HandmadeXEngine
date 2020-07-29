#pragma once

#ifndef XENGINE_CORE_H
#define XENGINE_CORE_H

#include "xe_types.h"
#include <string>

namespace xe_core
{
    struct XEFile
    {
        uint32 size;
        void *data;
    };

    XEFile readWholeFile(const char *file_name);
    std::string readFileString(const char *file_path);
    unsigned char* loadTextureFromDisc(const char* path, int &width, int &height, int &channels, int flag, bool32 flip);
    float *loadTextureFloatFromDisc(const char* path, int &width, int &height, int &channels, int flag, bool32 flip);
    void deleteData(void *data);
}

#endif // !XENGINE_CORE_H
