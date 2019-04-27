#pragma once

#include "../../ecs/entity.h"

#include <vector>

namespace XEngine
{
    class Scene
    {
    public:
        Scene(const char* name);
        
        void init();
        void addEntity(Entity *ent);
        void delEntity(Entity *ent);

    private:
        std::vector<Entity*> mEntity;


    };
}
