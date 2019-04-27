#pragma once

#ifndef ENTITY
#define ENTITY


#include "../geometry/model.h"
#include "../rendering/pipeline/material.h"
#include "../math/transforms.h"

namespace XEngine
{
    using namespace Rendering;
    using namespace Math;

    struct Entity
    {
        Assets::Model* model;
        Material* material;
        Transform* transf;
    };

}

#endif // !ENTITY

