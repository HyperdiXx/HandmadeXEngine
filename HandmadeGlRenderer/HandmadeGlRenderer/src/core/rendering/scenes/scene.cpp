#include "scene.h"

XEngine::Scene::Scene(const char * name)
{
    init();
}

void XEngine::Scene::init()
{
    for (size_t i = 0; i < mEntity.size(); ++i)
        mEntity[i] = nullptr;
}

void XEngine::Scene::addEntity(Entity * ent)
{
    mEntity.push_back(ent);
}

void XEngine::Scene::delEntity(Entity * ent)
{
    mEntity.pop_back();
}
