#include "scene.h"

XEngine::Scene::Scene(const char * name)
{
    init();
}

void XEngine::Scene::init()
{
    /*for (size_t i = 0; i < mEntity.size(); ++i)
        mEntity[i] = new Entity();*/
}

void XEngine::Scene::addEntity(Entity *ent)
{
    mEntity.push_back(ent);
}

void XEngine::Scene::delEntity(Entity *ent)
{
    mEntity.pop_back();
}

void XEngine::Scene::drawScene()
{
    for (size_t i = 0; i < mEntity.size(); ++i)
        mEntity[i]->model->drawMesh(mEntity[i]->material->getShader());
}
