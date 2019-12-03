#pragma once

#ifndef TYPES_H
#define TYPES_H

#if defined _WIN64
    #define WINDOWS
#endif // _WIN64

#if defined WINDOWS
#include <stdint.h>
#endif // WINDOWS

#if defined( __LINUX__ ) || defined( __OSX__ )
#include <sys/types.h>
#endif

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef int32 bool32;

typedef float real32;
typedef double real64;

#endif // !TYPES_H

