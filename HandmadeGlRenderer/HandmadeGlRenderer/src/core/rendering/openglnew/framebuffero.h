#pragma once

#ifndef FBO
#define FBO

#include "../../../application/xenpch.h"
#include "../../types.h"

class __declspec(dllexport) FrameBuffer
{
public:
    void createFBOforDefShading(uint32 GPos, uint32 GNormal, uint32 GSpeccolor, uint32 GBuffer, uint32 rboDepth);
    void bindFBO(uint32 GBuffer);

    void createShadows();
};



#endif // !FBO

