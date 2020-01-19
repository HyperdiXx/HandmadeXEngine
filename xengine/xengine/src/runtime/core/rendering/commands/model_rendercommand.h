#pragma once

#ifndef MODEL_COMMAND_H
#define MODEL_COMMAND_H

#include "rendercommand.h"

#include <runtime/geometry/model.h>
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
            void set(Assets::Model* model, Shader* shader, glm::mat4& matrix)
            {
                m_model = model;
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
                using namespace Assets;

                m_shader->bind();
                m_shader->setMat4("model", m_model_matrix);
                m_shader->setMat4("viewproj", m_proj_matrix * m_view_matrix);

                Node* root = m_model->root;

                for (uint32 i = 0; i < root->children.size(); i++)
                {
                    Node* curr_node = root->children[i];

                    for (uint32 j = 0; j < curr_node->meshes.size(); j++)
                    {
                        Mesh *cur_mesh = curr_node->meshes.at(j);
                        draw_mesh(cur_mesh);
                    }  
                }

                m_shader->unbind();
            };

            void draw_mesh(Assets::Mesh* mesh)
            {
                uint32 diffuseN = 1;
                uint32 normalN = 1;
                uint32 specularN = 1;

                for (uint32 i = 0; i < mesh->mesh_textures.size(); i++)
                {
                    // @Refactor!!!
                    Texture2D *mesh_texture = mesh->mesh_textures[i].texture;                   
                    mesh_texture->activate(i);

                    std::string name = mesh->mesh_textures[i].type;
                    std::string num;
                    
                    if (name == "tex_diff")
                        num = std::to_string(diffuseN++);
                    else if (name == "tex_norm")
                        num = std::to_string(normalN++);
                    else if (name == "tex_spec")
                        num = std::to_string(specularN++);

                    m_shader->setInt((name + num).c_str(), i);
                    mesh_texture->bind();
                }

                if (mesh->vertices.size() > 0)
                {
                    glBindVertexArray(mesh->get_vao());
                    RenderCommand::draw_indexed(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, 0);
                    glBindVertexArray(0);
                }           
            }


        private:           
            glm::mat4 m_model_matrix = glm::mat4(1.0f);
            glm::mat4 m_view_matrix = glm::mat4(1.0f);
            glm::mat4 m_proj_matrix = glm::mat4(1.0f);
            RenderCommandType m_type;
            Assets::Model *m_model;
            Shader *m_shader;
        };
    }
}
#endif // !MODEL_COMMAND_H

