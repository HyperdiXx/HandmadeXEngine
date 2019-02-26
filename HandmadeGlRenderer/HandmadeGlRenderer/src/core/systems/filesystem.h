#pragma once


#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>

struct FileSystem
{
    static std::wstring sDataFolder;
    static std::wstring sModelsSubFolder;
    static std::wstring sScriptsSubFolder;
    static std::wstring sShaderSubFolder;
    static std::wstring sTextureSubFolder;
};


std::wstring FileSystemGetLogFolder();

#endif // !FILESYSTEM_H
