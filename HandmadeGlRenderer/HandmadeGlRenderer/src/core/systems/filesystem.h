#pragma once


#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "src/core/xenginedll.h"

#include <string>



struct XENGINE_API FileSystem
{
    static std::wstring sDataFolder;
    static std::wstring sModelsSubFolder;
    static std::wstring sScriptsSubFolder;
    static std::wstring sShaderSubFolder;
    static std::wstring sTextureSubFolder;
};


std::wstring XENGINE_API FileSystemGetLogFolder();

#endif // !FILESYSTEM_H
