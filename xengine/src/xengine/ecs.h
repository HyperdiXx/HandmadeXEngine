
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
    Vec3 target = createVec3(0.0f, 0.0f, -1.0f);
    Vec3 up = createVec3(0.0f, 1.0f, 0.0f);
    Vec3 right;
    Vec3 world_up;

    Matrix4x4 projection = createMat4x4();

    Camera3D(Vec3 position = createVec3(0.0f, 0.0f, 3.0f))
    {
        pos = position;
        cam_yaw = c_yaw;
        cam_pitch = c_pitch;
        cam_zoom = c_zoom;
        speed = c_speed;
        world_up = up;
        updateCamera();
    }

    Matrix4x4 &getProjectionMatrix()
    {
        if (!is_inited)
        {
            projection = perspectiveMat(fov, aspect_ratio, near_plane, far_plane);
            is_inited = true;
        }

        return projection;
    }

    Matrix4x4 getViewMatrix()
    {
        return lookAt(pos, pos + target, up);
    }

    Matrix4x4 getViewProjection()
    {
        return getProjectionMatrix() * getViewMatrix();
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
        
        //target = Normalize(front);
        //right  = Normalize(CrossProduct(target, world_up));
        //up     = Normalize(CrossProduct(right, target));       
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
