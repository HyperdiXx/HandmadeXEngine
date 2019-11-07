#pragma once

#ifdef XENGINE_WINDOWS
    #ifdef XENGINE_LIB
        #define XENGINE_API __declspec(dllexport)
    #else
        #define XENGINE_API __declspec(dllimport)
    #endif
#else
    //LINUX....
#endif

