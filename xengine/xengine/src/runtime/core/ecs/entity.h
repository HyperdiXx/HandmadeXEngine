#pragma once

#ifndef ENTITY
#define ENTITY

#include "component.h"
#include <runtime/types.h>
#include <xenpch.h>

namespace XEngine
{ 
    
    struct Entity
    {
        uint32 id;
    };

    /*Entity create_entity()
    {
        static Entity n = {};
        n.id++;
        return n;
    }*/

}
#endif // !ENTITY

