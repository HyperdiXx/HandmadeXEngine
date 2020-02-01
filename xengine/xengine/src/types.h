
#ifndef TYPESFILE_H
#define TYPESFILE_H

#ifdef _MSC_VER
#pragma once
#endif  

#include <math.h>
#include <stdint.h>

#if defined( __LINUX__ ) || defined( __OSX__ )
#include <sys/types.h>
#endif

#define Pi32 3.14159265359f

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
