#pragma once

#ifndef XE_LAYER_H
#define XE_LAYER_H

//#include "xe_types.h"
//#include "xenpch.h"

//#include "xe_ecs.h"

class Layer
{
public:

    virtual ~Layer() {}

    virtual void init() = 0;
    virtual void render() = 0;
    virtual void update(real32 dt) = 0;
};

#endif // !XE_LAYER_H

