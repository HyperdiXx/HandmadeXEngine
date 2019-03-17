#include "log.h"

#include "../../xenpch.h"
#include "../systems/filesystem.h"

using namespace XEngine;

//XEngine::Log& XEngine::getLog()
//{
//    return Instance;
//}

bool32 XEngine::openFile(Log *a)
{
    FileSystem fs;
    std::wstring filename = FileSystemGetLogFolder() + L"\\Log.txt";

    a->logstream.open(filename.c_str());

    
    return(true);

}

bool32 XEngine::closeFile(Log *a)
{
    return (true);
}


bool32 XEngine::writeToConsole(Log *i)
{
    std::cout << i->text << "\n";

    return (true);
}
//
//bool32 XEngine::writeToConsole(std::wstring& t)
//{
//    return bool32();
//}
//
