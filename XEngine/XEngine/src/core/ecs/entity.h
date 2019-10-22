#pragma once

#ifndef ENTITY
#define ENTITY

#include "../geometry/model.h"
#include "../rendering/pipeline/materials/basicmaterial.h"
#include "../rendering/pipeline/materials/bpmaterial.h"
#include "../rendering/pipeline/materials/pbrmaterial.h"

#include <xemath.h>

namespace XEngine
{
    using namespace Rendering;
    using namespace Math;

    class Entity
    {
    public:
        Entity() {};
        Entity(Assets::Model *mesh, Rendering::BasicMaterial *m)
        {
            model = mesh;
            material = m;
        }

        Entity(Assets::Model *mesh, Rendering::PBRMaterial *m)
        {
            model = mesh;
            material = m;
        }

        Entity(Assets::Model *mesh, Rendering::BPMaterial *m)
        {
            model = mesh;
            material = m;
        }

        Assets::Model *model;
        Rendering::Material *material;
    };

}


#endif // !ENTITY

