#pragma once

#ifndef ENTITY
#define ENTITY

#include "../geometry/model.h"
#include "../rendering/pipeline/materials/basicmaterial.h"
#include "../rendering/pipeline/materials/bpmaterial.h"
#include "../rendering/pipeline/materials/pbrmaterial.h"
#include "../math/transforms.h"

namespace XEngine
{
    using namespace Rendering;
    using namespace Math;

    class Entity : Component
    {
    public:
        Entity() {};
        Entity(Assets::Model *mesh, Rendering::BasicMaterial *m, Math::Transform *tr)
        {
            model = mesh;
            material = m;
            transf = tr;
        }

        Entity(Assets::Model *mesh, Rendering::PBRMaterial *m, Math::Transform *tr)
        {
            model = mesh;
            material = m;
            transf = tr;
        }

        Entity(Assets::Model *mesh, Rendering::BPMaterial *m, Math::Transform *tr)
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

