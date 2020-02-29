#pragma once

#ifndef MODEL_COMMAND_H
#define MODEL_COMMAND_H

#include "rendercommand.h"

#include "xe_assets.h"
#include <glm/glm.hpp>

namespace XEngine
{
    namespace Rendering
    {
        class ModelRenderCommand : public RenderCommand
        {
        public:
            ModelRenderCommand(RenderCommandType type) : m_type(type) {}
            
            // @Info: set as material later on
            void set(xe_assets::model* mod, xe_graphics::shader* shader, glm::mat4& matrix)
            {
                m_model = mod;
                m_shader = shader;
                m_model_matrix = matrix;
            }

            void set_view_projection(glm::mat4& view, glm::mat4& projection)
            {
                m_view_matrix = view;
                m_proj_matrix = projection;
            }

            virtual void execute()
            {
                xe_graphics::graphics_device *device = xe_render::get_device();

                // @move to GL Render device abst and setup here
                glEnable(GL_DEPTH_TEST);

                device->bind_shader(m_shader);
                device->set_mat4("model", m_model_matrix, m_shader);
                device->set_mat4("viewproj", m_proj_matrix * m_view_matrix, m_shader);
                
                //m_shader->bind();
                //m_shader->setMat4("model", m_model_matrix);
                //m_shader->setMat4("viewproj", m_proj_matrix * m_view_matrix);

                xe_assets::node *root = m_model->root;

                for (uint32 i = 0; i < root->children.size(); i++)
                {
                    xe_assets::node* curr_node = root->children[i];

                    for (uint32 j = 0; j < curr_node->meshes.size(); j++)
                    {
                        xe_assets::mesh *cur_mesh = curr_node->meshes.at(j);
                        draw_mesh(cur_mesh);
                    }  
                }

                device->unbind_shader();

                //m_shader->unbind();


                // @move to GL Render device abst and setup here
                glDisable(GL_DEPTH_TEST);
            };

            void draw_mesh(xe_assets::mesh* mesh)
            {
                xe_graphics::graphics_device *device = xe_render::get_device();

                uint32 diffuseN = 1;
                uint32 normalN = 1;
                uint32 specularN = 1;

                for (uint32 i = 0; i < mesh->mesh_textures.size(); i++)
                {
                    // @Refactor!!!
                    xe_graphics::texture2D *mesh_texture = mesh->mesh_textures[i].texture;                   
                    //mesh_texture->activate(i);

                    std::string name = mesh->mesh_textures[i].type;
                    std::string num;
                    
                    if (name == "tex_diff")
                        num = std::to_string(diffuseN++);
                    else if (name == "tex_norm")
                        num = std::to_string(normalN++);
                    else if (name == "tex_spec")
                        num = std::to_string(specularN++);

                    device->set_int((name + num).c_str(), i, m_shader);
                    //mesh_texture->bind();
                }

                if (mesh->vertices.size() > 0)
                {
                    //glBindVertexArray(mesh->get_vao());
                    RenderCommand::draw_indexed(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, 0);
                    glBindVertexArray(0);
                }           
            }


        private:           
            glm::mat4 m_model_matrix = glm::mat4(1.0f);
            glm::mat4 m_view_matrix = glm::mat4(1.0f);
            glm::mat4 m_proj_matrix = glm::mat4(1.0f);
            RenderCommandType m_type;
            xe_assets::model *m_model;
            xe_graphics::shader *m_shader;
        };
    }
}
#endif // !MODEL_COMMAND_H

