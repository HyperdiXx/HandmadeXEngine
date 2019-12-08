#pragma once

#ifndef ASSERT_H
#define ASSERT_H

#define XECORE_DEBUG_BREAK() __debugbreak()

// TODO: log 

#define assert(x) if(!(x)) { XECORE_DEBUG_BREAK(); }

#endif // !ASSERT_H
