#pragma once


#ifdef XENGINE_WINDOWS
    #ifdef XENGINE_DLL
        #define XENGINE_API __declspec(dllexport)
    #else   
        #define XENGINE_API __declspec(dllimport)
    #endif 
#else 
    #error Define other platform
#endif 

