
#ifndef ECS_H
#define ECS_H

typedef uint32 EntityID;
global uint32 idEntity = 1;

struct Entity
{
    Entity() : id(idEntity++) {};    

    EntityID id;
};

enum CSType
{
    TRANSFORM,
    CAMERA2D,
    CAMERA3D,
    STATIC_MODEL,
    ANIMATED_MODEL,
    IMAGE
};

struct TransformComponent
{
    Vec3 position;
    Quaternion quat;
    Vec3 scale;
};

struct Camera2DComponent
{

};

struct Camera3DComponent
{

};

struct DirLightComponent
{
    Vec3 color;
};

struct PointLightComponent
{

};

struct SpotLightComponent
{

};

struct Component
{
    CSType type;

    EntityID entity_id;

    union
    {
        TransformComponent  transform;
        Camera2DComponent   camera2D;
        Camera3DComponent   camera3D;
        DirLightComponent   dirLight;
        PointLightComponent pointLight;
        SpotLightComponent  spotLight;
    };
};

struct TransformSystem
{
    void update()
    {
        int a = 10;
        int counter = 0;
        counter += a;
    }
};

struct RenderSystem
{
    void update()
    {
        int a = 1;

        for (uint32 i = 0; i < 1000; ++i)
        {
            ++a;
        }
    }
};

struct System
{
    enum class SystemType
    {
        RenderSystem,
        TransformSystem
    };

    System() {};
    System(SystemType t) : type(t) {};

    SystemType type;

    union
    {
        TransformSystem transform_system;
        RenderSystem render_system;
    };
};

class ECSManager
{
public:

    ECSManager();

    Entity createEntity();
    void removeEntity();

    void createComponent(EntityID id, uint32 component_id);
    void removeComponent(EntityID id, uint32 component_id);

    void createSystem(System system);
    void removeSystem(uint32 system_id);

    void updateSystems();

private:

    uint32 active_ent = 0;

    ECSManager(const ECSManager&) = delete;
    ECSManager(ECSManager &&) = delete;
    
    std::queue<Entity> entities;
    DynArray<System> systems;
};

#endif // !ECS_H
