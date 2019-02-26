#include "model.h"

void setupmeshopengl(Mesh* mesh)
{
    glGenVertexArrays(1, &mesh->VAO);
    glGenBuffers(1, &mesh->VBO);
    glGenBuffers(1, &mesh->EBO);

    glBindVertexArray(mesh->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);

    glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(VertexX), &mesh->vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
    glBufferData(GL_ARRAY_BUFFER, mesh->indices.size() * sizeof(uint32), &mesh->indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexX), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexX), (void*)offsetof(VertexX, normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexX), (void*)offsetof(VertexX, uv));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexX), (void*)offsetof(VertexX, tangent));

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(VertexX), (void*)offsetof(VertexX, bitangent));

    glBindVertexArray(0);
}

void drawMesh(Mesh *mesh, Shader *shader)
{
    // bind appropriate textures
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (unsigned int i = 0; i < mesh->textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = mesh->textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++); // transfer unsigned int to stream
        else if (name == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to stream
        else if (name == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to stream

                                                 // now set the sampler to the correct texture unit
        glUniform1i(glGetUniformLocation(shader->ID, (name + number).c_str()), i);
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, mesh->textures[i].id);
    }

    // draw mesh
    glBindVertexArray(mesh->VAO);
    glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}

void drawMeshFrom(Model* model, Shader* shader)
{
    for (uint32 i = 0; i < model->meshs.size(); i++)
        drawMesh(&model->meshs[i], shader);
 
}

void loadModelopengl(Model *model)
{
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(model->filename, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }    
    model->dir = model->filename.substr(0, model->filename.find_last_of('/'));

    processNode(scene->mRootNode, scene, model);
}

void processNode(aiNode *node, const aiScene *s, Model *model)
{
    for (uint16 i = 0; i < node->mNumMeshes; ++i)
    {
        aiMesh *mesh = s->mMeshes[node->mMeshes[i]];
        model->meshs.push_back(processMesh(model, mesh, s));
    }
    
    for (uint16 i = 0; i < node->mNumChildren; ++i)
    {
        processNode(node->mChildren[i], s, model);
    }

}


Mesh setupMesh(std::vector<VertexX> vert, std::vector<uint32> ind, std::vector<Texture> text)
{
    Mesh ret;

    ret.vertices = vert;
    ret.indices = ind;
    ret.textures = text;

    return (ret);
}
Mesh processMesh(Model* model, aiMesh *mesh, const aiScene* scene)
{
    std::vector<VertexX> vertices;
    std::vector<uint32> indices;
    std::vector<Texture> textures;

    for (uint32 i = 0; i < mesh->mNumVertices; ++i)
    {
        VertexX vertex;
        glm::vec3 v;
        v.x = mesh->mVertices[i].x;
        v.y = mesh->mVertices[i].y;
        v.z = mesh->mVertices[i].z;
        vertex.pos = v;

        v.x = mesh->mNormals[i].x;
        v.y = mesh->mNormals[i].y;
        v.z = mesh->mNormals[i].z;
        vertex.normal = v;

        if (mesh->mTextureCoords[0])
        {
            glm::vec2 vec;

            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.uv = vec;
        }
        else
        {
            vertex.uv = glm::vec2(0.0f, 0.0f);
        }

        if (mesh->mTangents)
        {
            v.x = mesh->mTangents[i].x;
            v.y = mesh->mTangents[i].y;
            v.z = mesh->mTangents[i].z;
            vertex.tangent = v;
        }
        
        if (mesh->mBitangents)
        {
            v.x = mesh->mBitangents[i].x;
            v.y = mesh->mBitangents[i].y;
            v.z = mesh->mBitangents[i].z;
            vertex.bitangent = v;
        }
        

        vertices.push_back(vertex);
    }

    for (uint32 i = 0; i < mesh->mNumFaces; ++i)
    {
        aiFace face = mesh->mFaces[i];
        for (uint32 j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    std::vector<Texture> diffuseMaps = loadTextureVec(model, material, aiTextureType_DIFFUSE, (char*)"texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    std::vector<Texture> specularMaps = loadTextureVec(model, material, aiTextureType_SPECULAR, (char*)"texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    std::vector<Texture> normalMaps = loadTextureVec(model, material, aiTextureType_HEIGHT, (char*)"texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

    std::vector<Texture> heightMaps = loadTextureVec(model, material, aiTextureType_AMBIENT, (char*)"texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    Mesh ret = setupMesh(vertices, indices, textures);

    return (ret); 
}

std::vector<Texture> loadTextureVec(Model *model, aiMaterial *mat, aiTextureType type, char* name)
{
    std::vector<Texture> textures;
    for (uint32 i = 0; i < mat->GetTextureCount(type); ++i)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
        bool skip = false;
        for (unsigned int j = 0; j < model->texturesl.size(); j++)
        {
            if (std::strcmp(model->texturesl[j].name.data(), str.C_Str()) == 0)
            {
                textures.push_back(model->texturesl[j]);
                skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                break;
            }
        }
        if (!skip)
        {   // if texture hasn't been loaded already, load it
            Texture texture;
            texture.id = readtexturefromfile(str.C_Str(), model->dir);
            texture.type = name;
            texture.name = str.C_Str();
            textures.push_back(texture);
            model->texturesl.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
        }
    }
    return textures;
}

uint32 readtexturefromfile(const char* path, std::string &namedir)
{
    std::string filename = std::string(path);
    filename = namedir + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
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