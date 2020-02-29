

#include "model.h"

#include <rendering/api/base/texture2d.h>
#include <rendering/render/render.h>
#include <rendering/api/base/vertexarray.h>
#include <rendering/api/base/vertexbuffer.h>
#include <rendering/api/base/indexbuffer.h>

#include <runtime/animation/animation.h>

using namespace XEngine;
using namespace Assets;
using namespace Rendering;

/*void Mesh::setup_mesh()
{     
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(StaticVertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(StaticVertex), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(StaticVertex), (void*)offsetof(StaticVertex, normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(StaticVertex), (void*)offsetof(StaticVertex, uv));

    // @tangent & @bitangent
    //glEnableVertexAttribArray(3);
    //glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(V3F_UV2F_N3F_T3F_BI3F), (void*)offsetof(V3F_UV2F_N3F_T3F_BI3F, tangent));

    //glEnableVertexAttribArray(4);
    //glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(V3F_UV2F_N3F_T3F_BI3F), (void*)offsetof(V3F_UV2F_N3F_T3F_BI3F, bitangent));

    glBindVertexArray(0);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

BPMaterialSpec Model::loadMaterial(aiMaterial* mat)
{
    BPMaterialSpec material;
    //aiColor3D color(0.f, 0.f, 0.f);
    float shininess;

    //mat->Get(AI_MATKEY_COLOR_DIFFUSE, color);
    //material.dif = vec3f(color.r, color.b, color.g);

    //mat->Get(AI_MATKEY_COLOR_AMBIENT, color);
    //material.ambient = vec3f(color.r, color.b, color.g);

    //mat->Get(AI_MATKEY_COLOR_SPECULAR, color);
    //material.spec = vec3f(color.r, color.b, color.g);

    //mat->Get(AI_MATKEY_SHININESS, shininess);
    //material.shiness = shininess;

    return material;
}

void Mesh::add_vertex(StaticVertex vertex)
{
    vertices.push_back(vertex);
}

void Mesh::add_index(uint32 ind)
{
    indices.push_back(ind);
}

void Node::add_child(Node *child)
{
    children.push_back(child);
}

void Node::add_mesh(Mesh *mesh)
{
    meshes.emplace_back(mesh);
}

std::vector<TextureWrapper> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
{
    using namespace Rendering;

    std::vector<TextureWrapper> textures;
    for (uint32 i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);

        bool skip_parsing = false;
        for (uint32 j = 0; j < model_textures.size(); j++)
        {
            if (std::strcmp(model_textures[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(model_textures[j]);
                skip_parsing = true; 
                break;
            }
        }
        
        if (!skip_parsing)
        {      
            TextureWrapper texture_wrapper = {};            
            // @Optimize 
            // Raw pointer to CPU texture. MB Wrong 
            texture_wrapper.texture = Texture2D::create(str.C_Str(), this->parent_dir.c_str());
            texture_wrapper.type = typeName;
            texture_wrapper.path = str.C_Str();
            textures.push_back(texture_wrapper);
            model_textures.push_back(texture_wrapper);
        }
    }
    return textures;
}

void XEngine::Assets::AnimatedMesh::add_weight(uint32 vert_index, uint32 bone_index, GLuint bone_id, GLfloat weight)
{
    vertices[vert_index].boneIDs[bone_index] = bone_id;
    vertices[vert_index].weights[bone_index] = weight;
}

void XEngine::Assets::AnimatedMesh::add_vertex(AnimVertex vertex)
{
    vertices.push_back(vertex);
}

void XEngine::Assets::AnimatedMesh::add_index(uint32 ind)
{
    indices.push_back(ind);
}

void XEngine::Assets::AnimatedModel::add_bone(std::shared_ptr<Bone> bone)
{
    
}

void XEngine::Assets::AnimatedModel::add_animation(Animation *animation)
{
    m_anim_map[animation->get_name()] = m_animations.size();
    m_animations.emplace_back(std::move(animation));
}*/
