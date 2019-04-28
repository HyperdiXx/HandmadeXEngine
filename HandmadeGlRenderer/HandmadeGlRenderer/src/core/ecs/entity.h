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

    class Entity
    {
    public:
        Entity() {};
        Entity(Assets::Model *mesh, Rendering::Material *m, Math::Transform *tr)
        {
            model = mesh;
            material = m;
            transf = tr;
        }

        Assets::Model *model;
        Rendering::Material *material;
        Math::Transform *transf;
    };

}


#endif // !ENTITY

