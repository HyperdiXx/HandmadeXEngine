
#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <assert.h>
#include <fstream>
#include <math.h>

// Remove 
#include <vector>
#include <unordered_set>
#include <queue>
#include <deque>
#include <map>
#include <unordered_map>
#include <string>

#include <thread>
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <algorithm>

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

#define global static
#define internal static

#define ArrayCount(a) (sizeof(a) / sizeof((a)[0]))
#define Bytes(n)      (n)
#define Kilobytes(n)  (n << 10)
#define Megabytes(n)  (n << 20)
#define Gigabytes(n)  (((u64)n) << 30)
#define Terabytes(n)  (((u64)n) << 40)

#define Max(a, b) (a > b ? a : b)

#endif // !COMMON_H
