

#include "model.h"

#include <runtime/core/rendering/api/base/texture2d.h>
#include <runtime/core/rendering/render/render.h>
#include <runtime/core/rendering/api/base/vertexarray.h>
#include <runtime/core/rendering/api/base/vertexbuffer.h>
#include <runtime/core/rendering/api/base/indexbuffer.h>

using namespace XEngine;
using namespace Assets;
using namespace Rendering;

void Mesh::setup_mesh()
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

    /*for (uint32 i = 0; i < BONES_COUNT; i++)
    {
        glVertexAttribPointer(3 + i, 1, GL_FLOAT, GL_FALSE, sizeof(AnimVertex), (void*)(offsetof(AnimVertex, boneIDs) + sizeof(real32) * i));
        glEnableVertexAttribArray(3 + i);
    }

    for (uint32 i = 0; i < BONES_COUNT; i++)
    {
        glVertexAttribPointer(9 + i, 1, GL_FLOAT, GL_FALSE, sizeof(AnimVertex), (void*)(offsetof(AnimVertex, weights) + sizeof(float) * i));
        glEnableVertexAttribArray(9 + i);
    }*/

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

/*void Mesh::renderMeshes(Shader* shader)
{
    uint32 diffuseNr = 1;
    uint32 specularNr = 1;
    uint32 normalNr = 1;
    uint32 heightNr = 1;
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); 
        std::string number;
        std::string name = textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++);
        else if (name == "texture_normal")
            number = std::to_string(normalNr++); 
        else if (name == "texture_height")
            number = std::to_string(heightNr++); 
                                                 
        glUniform1i(glGetUniformLocation(shader->getID(), (name + number).c_str()), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
}*/

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

/*uint32 Model::loadtexture2DFromDir(const std::string path, const std::string & dir, bool gamma)
{
    std::string filename = path;
    filename = dir + '/' + filename;

    uint32 textureID;
    glGenTextures(1, &textureID);

    int width, height, sizechannels;

    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &sizechannels, 0);
    if (data)
    {
        GLenum format;
        if (sizechannels == 1)
            format = GL_RED;
        else if (sizechannels == 3)
            format = GL_RGB;
        else if (sizechannels == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
*/