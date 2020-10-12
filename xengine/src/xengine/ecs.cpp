
ECSManager::ECSManager()
{
    entities = {};
    systems  = createDynArray<System>();
}

Entity ECSManager::createEntity()
{
    Entity ent = {};

    entities.push(ent);
    
    ++active_ent;
    
    return ent;
}

void ECSManager::removeEntity()
{
    assert(entities.size() != 0);
    
    --active_ent;
    entities.pop();
}

void ECSManager::updateSystems()
{
    for (uint32 i = 0; i < systems.size(); ++i)
    {
        switch (systems[i].type)
        {
        case System::SystemType::TransformSystem:
        {
            systems[i].transform_system.update();
        } break;
        case System::SystemType::RenderSystem:
        {
            systems[i].render_system.update();
        } break;
        default:
            break;
        }    
    }
}

void ECSManager::createSystem(System system)
{
    systems.push_back(system);
}

void ECSManager::removeSystem(uint32 system_id)
{

}

internal System::SystemType convertToSystemType(const char* type_name)
{
    System::SystemType result = {};

    if (strEquals(type_name, "TransformSystem"))
    {
        result = System::SystemType::TransformSystem;
    }
    else if (strEquals(type_name, "RenderSystem"))
    {
        result = System::SystemType::RenderSystem;
    }

    return result;
}

