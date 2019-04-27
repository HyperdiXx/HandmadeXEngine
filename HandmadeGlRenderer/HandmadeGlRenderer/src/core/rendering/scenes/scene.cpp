#include "scene.h"

XEngine::Scene::Scene(const char * name)
{
    init();
}

XEngine::Scene::~Scene()
{
    for (int i = 0; i < mEntity.size(); ++i)
        delete mEntity[i];
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

void XEngine::Scene::drawScene()
{
    for (size_t i = 0; i < mEntity.size(); ++i)
        mEntity[i]->model->drawMesh(mEntity[i]->material->getShader());
}

void XEngine::Scene::clear()
{
    for (size_t i = 0; i < mEntity.size(); ++i)
        delete mEntity[i];
}

void XEngine::Scene::clearEnt(int ind)
{
    if(ind >= 0)
        delete mEntity[ind];
}
