
#ifndef PLATFORM_H
#define PLATFORM_H

typedef struct FileType
{
    char* file_name;
    char* file_ext;
    char* relative_path;

    bool operator==(const FileType& rhs) const
    {
        return true;
    }
} FileType;

#ifdef PLATFORM_WINDOWS
    #include "win32\win32_platform.cpp"
#else 
    //Linux
#endif

#endif
