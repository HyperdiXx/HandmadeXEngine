#ifndef GL_LOADER_H
#define GL_LOADER_H

#if PLATFORM_WINDOWS
#include <windows.h>
#include <GL/GL.h>
#include "external/wglext.h"
#else
#error "OpenGL not supported on this platform!"
#endif
#include "external/glext.h"

#define GLProc(name, type) PFNGL##type##PROC gl##name = 0;
#include "opengl_functions.inc"
#undef GLProc

internal void
LoadAllOpenGLProcedures()
{
#define GLProc(name, type) gl##name = (PFNGL##type##PROC) p_state->LoadOpenGLProcedure("gl" #name);
#include "opengl_functions.inc"
#undef GLProc
}
#endif // !GL_LOADER_H
