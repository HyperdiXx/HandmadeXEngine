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

    enum ENTITY_TYPE
    {
        ENT_NONE, 
        ENT_STATIC_OBJECT,
        ENT_ANIMATED_OBJECT,
        ENT_CAMERA
    };

    class component
    {
    public:
        virtual ~component() {};
    };

    class entity
    {
    public:

        entity()
        {
            components.reserve(16);
            id = id_create++;
        }

        template<class T>
        inline T* find_component()
        {
            for (int i = 0; i < components.size(); ++i)
            {
                component *comp = components[i];

                if (dynamic_cast<T*>(comp))
                    return dynamic_cast<T*>(comp);
            }

            return nullptr;
        }
        
        void add_component(component *comp)
        {
            components.push_back(comp);
        }

        void set_entity_type(ENTITY_TYPE t) { type = t; }
        void set_active(bool32 val) { is_used = val; };
        inline bool32 active() { return is_used; }
        inline ENTITY_TYPE get_type() { return type; }
    private:
        uint32_t id;
        bool32 is_used = false;
        ENTITY_TYPE type = ENTITY_TYPE::ENT_NONE;

        std::vector<component*> components;
    };

    class transform_component : public component
    {
    public:
        uint32 state = 0;

        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

        glm::mat4 model_matrix = xe_render::IDENTITY_MATRIX;

        void set_transform(glm::vec3 &pos, glm::vec3 &rot, glm::vec3 &scale)
        {
            set_translation(pos.x, pos.y, pos.z);
            set_rotation(rot.x, rot.y, rot.z);
            set_scale(scale.x, scale.y, scale.z);
        }

        void set_translation(real32 x, real32 y, real32 z)
        {
            if (position.x != x || position.y != y || position.z != z)
            {
                position.x = x;
                position.y = y;
                position.z = z;
                set_dirty();
            }
        }

        void set_rotation(real32 x_eul, real32 y_eul, real32 z_eul)
        {
            if (rotation.x != x_eul || rotation.y != y_eul || rotation.z != z_eul)
            {
                scale.x = x_eul;
                scale.y = y_eul;
                scale.z = z_eul;
                set_dirty();
            }
        }

        void set_scale(real32 x, real32 y, real32 z)
        {
            if (scale.x != x || scale.y != y || scale.z != z)
            {
                scale.x = x;
                scale.y = y;
                scale.z = z;
                set_dirty();
            }
        }

        void set_dirty() { state = true; };
        inline bool32 is_dirty() const { return state; };
    };
   
    class update_component : public component
    {
    public:

        void update(float dt);
    
    };

    class quad_component : public component
    {
    public:
        xe_graphics::quad *quad_mesh;
    };

    class mesh_component : public component
    {
    public:
        xe_assets::model *model_asset;
        xe_graphics::texture2D *diffuse_texture;

        bool32 draw_with_color = false;
    };
    
    class camera2d_component : public component
    {
    public:
        real32 width = 0.0f;
        real32 height = 0.0f;        

        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);

        glm::mat4 view = glm::mat4(1.0f), projection, view_projection;
        glm::mat4 inv_vp;

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
    };


    class camera3d_component : public component
    {
    public:
        //@Config!!!
        const real32 c_yaw = -90.0f;
        const real32 c_pitch = 0.0f;
        const real32 c_sens = 0.1f;
        const real32 c_zoom = 45.0f;
        const real32 c_speed = 12.0f;

        real32 near_plane = 0.05f;
        real32 far_plane = 1000.0f;
        real32 fov = 45.0f;
        real32 aspect_ratio = (real32)1280 / (real32)720;

        real32 cam_yaw;
        real32 cam_pitch;
        real32 speed;

        bool32 is_setuped = false;
      
        glm::vec3 pos;
        glm::vec3 target = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 right;
        glm::vec3 world_up;

        glm::mat4 projection = glm::mat4(1.0f);

        camera3d_component(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f))
        {
            pos = position;
            cam_yaw = c_yaw;
            cam_pitch = c_pitch;
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

        void update_camera_dir()
        {
            glm::vec3 front;
            front.x = cos(glm::radians(c_yaw)) * cos(glm::radians(c_pitch));
            front.y = sin(glm::radians(c_pitch));
            front.z = sin(glm::radians(c_yaw)) * cos(glm::radians(c_pitch));
            target = glm::normalize(front);
            right = glm::normalize(glm::cross(target, world_up));
            up = glm::normalize(glm::cross(right, target));
        }
    };

    class material_component : public component
    {
    public:
        xe_graphics::shader *shader;

        xe_graphics::texture2D *diffuse;
        xe_graphics::texture2D *normal;
        xe_graphics::texture2D *specular;
        xe_graphics::texture2D *ao;
    };

    class spot_light : public component
    {
    public:
        real32 entensity;
        glm::vec3 color;

        real32 radius;
    };

    class point_light : public component
    {
    public:
        glm::vec3 direction;
    };

    class dir_light : public component
    {
    public:
        real32 entensity;
        glm::vec3 color;

        bool32 is_static;
        bool32 is_casting_shadows;
    };
}
#endif
