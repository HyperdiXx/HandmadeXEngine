#pragma once

#include <windows.h>

#define Assert(x) \
    if (!(x)) { MessageBoxA(0, #x, "Assertion Failure", MB_OK); __debugbreak();}

#define Check(x) \
    if (!(x)) { MessageBoxA(0, #x, "Check Failure", MB_OK); __debugbreak();}

#define CheckSucceeded(hresult) \
    Check(SUCCEEDED(hresult))
