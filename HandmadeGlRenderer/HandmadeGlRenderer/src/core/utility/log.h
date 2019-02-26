#pragma once

#ifndef LOG_H
#define LOG_H

#include "../types.h"
#include <string>
#include <fstream>

namespace XEngine
{
    struct Log
    {
        char* text;
        std::wofstream logstream;
    };

    static Log Instance;

    static Log& getLog();

    bool32 openFile(Log * a);
    bool32 closeFile(Log* a);

    bool32 writeToConsole(Log* i);
    //bool32 writeToConsole(std::wstring& t);
}
#endif // !LOG_H

