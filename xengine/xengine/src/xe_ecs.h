#pragma once

#ifndef XENGINE_ECS_H
#define XENGINE_ECS_H


#include <glm/glm.hpp>

namespace xe_ecs
{   
    //uint32_t entity;

    //static const uint32_t unset = 0;

    //static uint32_t create_entity()
    //{
    //    return entity++;
    //}

    struct transform_component
    {
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;

        glm::mat4 model = glm::mat4(1.0f);
    };

    struct camera_component
    {       
        float width = 0.0f;
        float height = 0.0f;
        float fov = 60.0f;

        float near_plane = 0.0f;
        float far_plane = 0.0f;

        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 pos = glm::vec3(0.0f, 0.0f, 1.0f);
        glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);

        glm::mat4 view, projection, view_projection;
        glm::mat4 inv_view, inv_projection, inv_vp;

        void setup_projection(float n, float f, float w, float h, float fov);
        void update_camera();
        void transform_camera(transform_component& transform);
    };
}
#endif
