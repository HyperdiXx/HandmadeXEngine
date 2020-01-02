#pragma once

#include "entity.h"

namespace XEngine
{
    template<typename Component>
    class ComponentManager
    {
    public:
        
        Component& create(Entity entity)
        {
            m_table[entity] = m_components.size();
            m_components.push_back(Component());
            m_entities.push_back(entity);

            return m_components.back();
        }

        bool32 is_contains(Entity entity) const
        {
            return m_table.find(entity) != m_table.end();
        }

        Entity get_entity(uint32 index) const { return m_entities[index]; }
        inline uint32 getCount() const { return m_components.size(); }

        Component& operator[](uint32 index) { return m_components[index]; }

    private:
        ComponentManager() {};
        ComponentManager(const ComponentManager&);
        ComponentManager& operator=(ComponentManager&);

    private:
        std::vector<Entity> m_entities;
        std::vector<Component> m_components;

        std::unordered_map<Entity, uint32> m_table;
        uint32 count;

    public:
        static ComponentManager& getInstance()
        {
            static ComponentManager instance;
            return instance;
        }

    };
}

