#pragma once

#ifndef XENGINE_CORE_H
#define XENGINE_CORE_H

namespace xe_core
{
    struct XEFile
    {
        uint32 size;
        void *data;
    };

    internal XEFile readWholeFile(const char *file_name);
    internal std::string readFileString(const char *file_path);
    internal unsigned char* loadTextureFromDisc(const char* path, int &width, int &height, int &channels, int flag, bool32 flip);
    internal float *loadTextureFloatFromDisc(const char* path, int &width, int &height, int &channels, int flag, bool32 flip);
    internal void deleteData(void *data);
}

#endif // !XENGINE_CORE_H
