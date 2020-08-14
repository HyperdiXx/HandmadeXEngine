
#pragma once

#ifndef XE_PLATFORM_H
#define XE_PLATFORM_H

#include "xe_config.h"

#ifdef _WIN32
    #define PLATFORM_WINDOWS
#else
#define PLATFORM_LINUX
#endif

#ifdef PLATFORM_WINDOWS
    #define XE_DEBUG
    #define WIN32_LEAN_AND_MEAN

#include <io.h>
#include <fcntl.h>
#include <windows.h>
#include <xe_types.h>
#include <memory>

#ifdef GAPI_DX11
#include <DirectXMath.h>
#include <DirectXPackedVector.h>       
#endif // 

#endif 

#ifdef PLATFORM_WINDOWS

#include "win32_platform.h"
    
#endif

#ifdef PLATFORM_LINUX

#include "linux_platform.h"

#endif

#endif // !XE_PLATFORM_H

