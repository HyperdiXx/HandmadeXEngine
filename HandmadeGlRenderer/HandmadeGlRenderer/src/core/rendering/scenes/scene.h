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

        void drawScene();
        void clear();
        void clearEnt(int ind);
    private:
        std::vector<Entity*> mEntity;


    };
}
