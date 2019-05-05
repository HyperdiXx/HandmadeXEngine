#pragma once

#ifndef ENTITY
#define ENTITY

#include "../geometry/model.h"
#include "../rendering/pipeline/materials/basicmaterial.h"
#include "../math/transforms.h"

namespace XEngine
{
    using namespace Rendering;
    using namespace Math;

    class Entity
    {
    public:
        Entity() {};
        Entity(Assets::Model *mesh, Rendering::BasicMaterial *m, Math::Transform *tr)
        {
            model = mesh;
            material = m;
            transf = tr;
        }

        Assets::Model *model;
        Rendering::BasicMaterial *material;
        Math::Transform *transf;
    };

}


#endif // !ENTITY

