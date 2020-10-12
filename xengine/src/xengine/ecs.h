
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
    void update();
};

struct System
{    
    CSType type;

    union
    {
        TransformSystem transform_system;
    };
};

class ECSManager
{
public:

    ECSManager() = default;

    EntityID createEntity();
    void removeEntity();

    void createComponent(EntityID id, uint32 component_id);
    void removeComponent(EntityID id, uint32 component_id);

    void createSystem(System *system);
    void removeSystem(uint32 system_id);

private:
    ECSManager(const ECSManager&) = delete;
    ECSManager(ECSManager &&) = delete;
    
    DynArray<Entity> entities;
};

#endif // !ECS_H
