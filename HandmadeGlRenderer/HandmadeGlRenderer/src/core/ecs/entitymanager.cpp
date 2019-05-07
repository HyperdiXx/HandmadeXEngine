
#include "entitymanager.h"



namespace XEngine
{
    void EntityManager::addEnitity(std::string name, Entity * ent)
    {
        count++;
        mEntities.insert(std::pair<std::string, Entity*>(name, ent));
    }

    Entity * EntityManager::getEntitybyName(std::string name)
    {
        return mEntities.at(name);
    }

}
