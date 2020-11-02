
#ifndef ECS_H
#define ECS_H

typedef uint32 EntityID;
global uint32 idEntity = 1;
typedef uint32 ComponentID;

enum class CSType
{
    TRANSFORM,
    CAMERA2D,
    CAMERA3D,
    STATIC_MODEL,
    ANIMATED_MODEL,
    IMAGE
};

class BaseComponent
{
public:
    BaseComponent(EntityID id) : handle(id) {}
    virtual ~BaseComponent() = default;

    void setEntityID(EntityID id) { handle = id; }

    EntityID getEntityID() const { return handle; }

private:

    EntityID handle;
};

class TransformComponentT : public BaseComponent
{
public:
    static constexpr ComponentID ID = (uint32)CSType::TRANSFORM;

};

struct Entity
{
    Entity() : id(idEntity++) {};    

    EntityID id;

    //std::unordered_map<ComponentID, BaseComponent*> components;
};

struct TransformComponent
{
    Vec3 position;
    Quaternion quat;
    Vec3 scale;
};

REFLECT(camera2d_comp) struct Camera2DComponent
{
    uint32 width, height;
};

struct Camera2D
{
    real32 width = 0.0f;
    real32 height = 0.0f;

    Vec3 position = createVec3(0.0f, 0.0f, 0.0f);
    Vec3 rotation = createVec3(0.0f, 0.0f, 0.0f);

    Matrix4x4 view = createMat4x4();
    Matrix4x4 projection = createMat4x4();
    Matrix4x4 view_projection = createMat4x4();
    Matrix4x4 inv_vp;

    bool32 is_inited = false;

    void setPos(const Vec3& pos) { position = pos; updateCamera(); };
    void setRotation(const Vec3& rot) { rotation = rot; updateCamera(); };
    void setRotation(const Quaternion &quat) {};

    void setupProjection(real32 left, real32 right, real32 bottom, real32 top)
    {
        projection = orthoMat(left, right, bottom, top, -1.0f, 1.0f);
        view_projection = projection * view;
    }

    void updateCamera()
    {
        Matrix4x4 transform = createMat4x4();
        translateMat(transform, position);

        view = inverseMat(transform);
        view_projection = projection * view;
    }

    const Vec3& getPosition() const { return position; }
    const Vec3& getRotation() const { return rotation; }
    const Matrix4x4& getView() const { return view; };

    const Matrix4x4& getViewProjection()
    {
        if (!is_inited)
        {
            setupProjection(0, width, height, 0);
            is_inited = true;
        }

        return view_projection;
    };

    const Matrix4x4& getProjection()
    {
        if (!is_inited)
        {
            setupProjection(0, width, 0, height);
            is_inited = true;
        }
        return projection;
    };
};

struct Camera3D
{
    const real32 c_yaw = -90.0f;
    const real32 c_pitch = 0.0f;
    const real32 c_sens = 0.2f;
    const real32 c_zoom = 45.0f;
    const real32 c_speed = 12.0f;

    real32 near_plane = 0.05f;
    real32 far_plane = 1000.0f;
    real32 fov = 45.0f;
    real32 aspect_ratio;

    real32 cam_yaw;
    real32 cam_pitch;
    real32 cam_zoom;
    real32 speed;

    bool32 is_inited = false;

    Vec3 pos;
    Vec3 target;
    Vec3 up;
    Vec3 right;
    Vec3 world_up;

    Matrix4x4 projection = createMat4x4();

    Camera3D(Vec3 position = createVec3(0.0f, 0.0f, 10.0f), Vec3 tar = createVec3(0.0f, 0.0f, 1.0f), Vec3 u = createVec3(0.0f, 1.0f, 0.0f))
    {
        pos = position;
        target = tar;
        up = u;
        cam_yaw = c_yaw;
        cam_pitch = c_pitch;
        cam_zoom = c_zoom;
        speed = c_speed;
        world_up = u;
        updateCamera();
    }

    Matrix4x4 &getProjectionMatrix()
    {
        if (!is_inited)
        {
            projection = perspectiveRH(fov, aspect_ratio, near_plane, far_plane);
            is_inited = true;
        }

        return projection;
    }

    Matrix4x4 getViewMatrix()
    {
        Vec3 target_vec = createVec3(0.0f, 0.0f, 1.0f);
        Vec3 up_vec = createVec3(0.0f, 1.0f, 0.0f);
        return lookAtRH(pos, Normalize(pos + target_vec), up_vec);
    }

    Matrix4x4 getViewProjectionMatrix()
    {
        Matrix4x4 &proj = getProjectionMatrix();
        Matrix4x4 view = getViewMatrix();
        Matrix4x4 res = proj * view;
        
        return res;
    }

    /*void mouse_move(real32 xoffset, real32 yoffset, real32 constrainPitch = true)
    {
        xoffset *= c_sens;
        yoffset *= c_sens;

        cam_yaw += xoffset;
        cam_pitch += yoffset;

        if (constrainPitch)
        {
            // @ Add clamp
            if (cam_pitch > 89.0f)
                cam_pitch = 89.0f;
            if (cam_pitch < -89.0f)
                cam_pitch = -89.0f;
        }

        update_camera_dir();
    }*/

    void updateCamera()
    {
        Vec3 front = createVec3(0.0f, 0.0f, 0.0f);

        front.x = cos(DegreesToRadians(cam_yaw)) * cos(DegreesToRadians(cam_pitch));
        front.y = sin(DegreesToRadians(cam_pitch));
        front.z = sin(DegreesToRadians(cam_yaw)) * cos(DegreesToRadians(cam_pitch));
        
        target = Normalize(front);
        right  = Normalize(CrossProduct(target, world_up));
        up     = Normalize(CrossProduct(right, target));       
    }
};

struct Camera3DComponent
{
    Camera3D *ptr_to_camera;
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
    DynArray<Component> components;
};

#endif // !ECS_H
