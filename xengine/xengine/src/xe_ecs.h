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

    private:
        uint32_t id;
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

        inline void set_dirty() {};
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
        float near_plane;
        float far_plane;
        float fov = 60.0f;

        void setup_projection();
        void update_input();

        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 pos = glm::vec3(0.0f, 0.0f, 1.0f);
        glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
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

    };

    class point_light : public component
    {
    public:
    };

    class dir_light : public component
    {
    public:
        real32 entensity;
        glm::vec3 color;
    };


}
#endif
