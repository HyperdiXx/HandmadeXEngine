#pragma once

#ifdef XENGINEOUT
#define XENGINE_API __declspec(dllexport)
#else
#define XENGINE_API __declspec(dllimport)

#endif //  XEPORT

