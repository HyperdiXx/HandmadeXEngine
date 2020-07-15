#pragma once

#ifndef XENGINE_ECS_H
#define XENGINE_ECS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "xe_graphics_resource.h"
#include "xe_assets.h"

#include <vector>

namespace xe_ecs
{
    static uint32_t id_create = 0;

    enum Component_TYPE
    {
        TRANSFORM,
        DIR_LIGHT,
        SPOT_LIGHT,
        POINT_LIGHT,
        QUAD_Component,
        MESH_Component,
        CAMERA2D,
        CAMERA3D,
        UPDATE,
        MATERIAL
    };

    enum ENTITY_TYPE
    {
        ENT_NONE, 
        ENT_STATIC_OBJECT,
        ENT_DIR_LIGHT,
        ENT_PRIMITIVE_OBJECT,
        ENT_ANIMATED_OBJECT,
        ENT_WATER,
        ENT_LINE,
        ENT_CAMERA
    };

    class Component
    {
    public:
        virtual ~Component() {};
    };

    class Entity
    {
    public:

        Entity()
        {
            Components.reserve(16);
            id = id_create++;
        }

        template<class T>
        inline T* findComponent()
        {
            for (int i = 0; i < Components.size(); ++i)
            {
                Component *comp = Components[i];

                if (dynamic_cast<T*>(comp))
                    return dynamic_cast<T*>(comp);
            }

            return nullptr;
        }
        
        void addComponent(Component *comp)
        {
            Components.push_back(comp);
        }

        void setEntityName(const std::string& name) { this->name = name; }
        void setEntityType(ENTITY_TYPE t) { type = t; }
        void setActive(bool32 val) { is_used = val; };
        inline bool32 active() { return is_used; }
        inline ENTITY_TYPE getType() { return type; }
        inline std::string& getName() { return name; }
    private:
        uint32_t id;
        bool32 is_used = false;
        ENTITY_TYPE type = ENTITY_TYPE::ENT_NONE;

        std::string name;
        std::vector<Component*> Components;
    };

    class TransformComponent : public Component
    {
    public:
        uint32 state = 0;

        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

        void setTransform(glm::vec3 &pos, glm::vec3 &rot, glm::vec3 &scale)
        {
            setTranslation(pos.x, pos.y, pos.z);
            setRotation(rot.x, rot.y, rot.z);
            setScale(scale.x, scale.y, scale.z);
        }

        void setTranslation(real32 x, real32 y, real32 z)
        {
            if (position.x != x || position.y != y || position.z != z)
            {
                position.x = x;
                position.y = y;
                position.z = z;
                setDirty();
            }
        }

        void setRotation(real32 x_eul, real32 y_eul, real32 z_eul)
        {
            if (rotation.x != x_eul || rotation.y != y_eul || rotation.z != z_eul)
            {
                scale.x = x_eul;
                scale.y = y_eul;
                scale.z = z_eul;
                setDirty();
            }
        }

        void setScale(real32 x, real32 y, real32 z)
        {
            if (scale.x != x || scale.y != y || scale.z != z)
            {
                scale.x = x;
                scale.y = y;
                scale.z = z;
                setDirty();
            }
        }

        void setDirty() { state = true; };
        inline bool32 isDirty() const { return state; };
    };
   
    class UpdateComponent : public Component
    {
    public:
        void update(float dt);
    };

    class QuadComponent : public Component
    {
    public:
        xe_graphics::Quad *quad_mesh;
    };

    class SphereComponent : public Component
    {
    public:
        xe_graphics::Sphere *sphere_mesh;
        xe_graphics::Texture2D *diffuse;
    };

    class MeshComponent : public Component
    {
    public:
        xe_assets::Model *model_asset;
        
        bool32 draw_with_color = false;
    };
    
    class Camera2DComponent : public Component
    {
    public:
        real32 width = 0.0f;
        real32 height = 0.0f;        

        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);

        glm::mat4 view = glm::mat4(1.0f), projection, view_projection;
        glm::mat4 inv_vp;

        bool32 is_setuped = false;

        void set_pos(const glm::vec3& pos) { position = pos; update_camera(); };
        void set_totation(glm::vec3& rot) { rotation = rot; update_camera(); };

        void setup_projection(real32 left, real32 right, real32 bottom, real32 top)
        {
            projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
            view_projection = projection * view;
        }

        void update_camera()
        {
            glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);

            view = glm::inverse(transform);
            view_projection = projection * view;
        }

        const glm::vec3& get_position() const { return position; }
        const glm::vec3& get_rotation() const { return rotation; }
        const glm::mat4& get_view() const { return view; };

        const glm::mat4& get_view_projection() 
        {
            if (!is_setuped)
            {
                setup_projection(0, width, 0, height);
                is_setuped = true;
            }

            return view_projection; 
        };

        const glm::mat4& get_projection() 
        {
            if (!is_setuped)
            {
                setup_projection(0, width, 0, height);
                is_setuped = true;
            }
            return projection;
        };

    };


    class Camera3DComponent : public Component
    {
    public:
        //@Config!!!
        const real32 c_yaw = -90.0f;
        const real32 c_pitch = 0.0f;
        const real32 c_sens = 0.2f;
        const real32 c_zoom = 45.0f;
        const real32 c_speed = 12.0f;

        real32 near_plane = 0.05f;
        real32 far_plane = 1000.0f;
        real32 fov = 45.0f;
        real32 aspect_ratio = (real32)1280 / (real32)720;

        real32 cam_yaw;
        real32 cam_pitch;
        real32 cam_zoom;
        real32 speed;

        bool32 is_setuped = false;
      
        glm::vec3 pos;
        glm::vec3 target = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 right;
        glm::vec3 world_up;

        glm::mat4 projection = glm::mat4(1.0f);

        Camera3DComponent(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f))
        {
            pos = position;
            cam_yaw = c_yaw;
            cam_pitch = c_pitch;
            cam_zoom = c_zoom;
            speed = c_speed;
            world_up = up;            
            update_camera_dir();
        }

        glm::mat4 &get_projection_matrix()
        {
            if (!is_setuped)
            {
                projection = glm::perspective(glm::radians(fov), aspect_ratio, near_plane, far_plane);
                is_setuped = true;
            }

            return projection;
        }

        glm::mat4 get_view_matrix()
        {
            return glm::lookAt(pos, pos + target, up);
        }

        glm::mat4 get_view_projection()
        {
            return projection * get_view_matrix();
        }

        void mouse_move(real32 xoffset, real32 yoffset, real32 constrainPitch = true)
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
        }

        void mouse_scroll(real32 yoffset)
        {
            if (cam_zoom >= 1.0f && cam_zoom <= 45.0f)
                cam_zoom -= yoffset;
            if (cam_zoom <= 1.0f)
                cam_zoom = 1.0f;
            if (cam_zoom >= 45.0f)
                cam_zoom = 45.0f;
        }

        void update_camera_dir()
        {
            glm::vec3 front;
            front.x = cos(glm::radians(cam_yaw)) * cos(glm::radians(cam_pitch));
            front.y = sin(glm::radians(cam_pitch));
            front.z = sin(glm::radians(cam_yaw)) * cos(glm::radians(cam_pitch));
            target = glm::normalize(front);
            right = glm::normalize(glm::cross(target, world_up));
            up = glm::normalize(glm::cross(right, target));
        }
    };

    class MaterialComponent : public Component
    {
    public:
        xe_graphics::Shader *shader;
        xe_graphics::Texture2D *texture;
    };

    class PBRMaterialComponent : public Component
    {
    public:
        xe_graphics::Shader *shader;

        xe_graphics::Texture2D *diffuse;
        xe_graphics::Texture2D *normal;
        xe_graphics::Texture2D *specular;
        xe_graphics::Texture2D *ao;

        real32 roughness = 0.0f;
        real32 metallness = 0.0f;
    };

    class LineMeshComponent : public Component
    {
    public:
        xe_graphics::Line *line_co;
    };

    class WaterComponent : public Component
    {
    public:

        xe_graphics::Texture2D *water_tex;
    };

    class SpotLight : public Component
    {
    public:
        glm::vec3 color;

        real32 intensity;
        real32 radius;
    };

    class PointLight : public Component
    {
    public:
        glm::vec3 direction;
    };

    class DirLight : public Component
    {
    public:
        real32 intensity;
        glm::vec3 color;

        bool32 is_static;
        bool32 is_casting_shadows;
    };

    class AnimationCotroller : public Component
    {
    public:
        
        void update(float dt);



    };

    /*template<typename Component>
    class Component_manager
    {
    public:

        Component& create(entity ent)
        {
            m_table[entity] = m_Components.size();
            m_Components.push_back(Component());
            m_entities.push_back(entity);

            return m_Components.back();
        }

        bool32 is_contains(entity ent) const
        {
            return m_table.find(ent) != m_table.end();
        }

        entity get_entity(uint32 index) const { return m_entities[index]; }
        inline uint32 getCount() const { return m_Components.size(); }

        Component& operator[](uint32 index) { return m_Components[index]; }

    private:
        Component_manager() {};
        Component_manager(const Component_manager&);
        Component_manager& operator=(Component_manager&);

    private:
        std::vector<Entity> m_entities;
        std::vector<Component> m_Components;

        std::unordered_map<Entity, uint32> m_table;
        uint32 count;
    }; */

}
#endif
