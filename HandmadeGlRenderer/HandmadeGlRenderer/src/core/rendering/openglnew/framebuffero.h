#pragma once

#ifndef FBO
#define FBO

#include<unordered_map>
#include "../../types.h"

class FrameBuffer
{
public:
    void createFBOforDefShading(uint32 GPos, uint32 GNormal, uint32 GSpeccolor, uint32 GBuffer, uint32 rboDepth);
    void bindFBO(uint32 GBuffer);

    void createShadows();
};



#endif // !FBO

