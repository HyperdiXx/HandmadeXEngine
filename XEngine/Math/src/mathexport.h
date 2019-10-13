#pragma once

#ifdef MATH_WINDOWS
    #ifdef MATH_BUILD_LIB
        #define MATH_API __declspec(dllexport)
    #else
        #define MATH_API __declspec(dllimport)
    #endif 
#else
    // Define math
#endif 

