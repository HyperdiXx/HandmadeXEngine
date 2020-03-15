#include "xe_assets.h"

#include "runtime/core/utility/log.h"

#include <glad/glad.h>

namespace xe_assets
{
    glm::mat4 xe_assets::transposeAiMat4(aiMatrix4x4 ai_mat)
    {
        glm::mat4 res;

        aiMatrix4x4 transposed = ai_mat.Transpose();

        for (uint32 i = 0; i < 4; i++)
        {
            for (uint32 j = 0; j < 4; j++)
            {
                res[i][j] = transposed[i][j];
            }
        }
        return res;
    }

    void parse_bones(anim_model *animmodel, anim_mesh *mesh, aiMesh *ai_mesh)
    {
        std::unordered_map<uint32, uint32> weight_count;

        for (uint32 i = 0; i < ai_mesh->mNumBones; i++)
        {
            aiBone* cur_bone = ai_mesh->mBones[i];

            std::shared_ptr<bone> current_bone{ new bone{cur_bone->mName.C_Str(), transposeAiMat4(cur_bone->mOffsetMatrix)} };

            for (uint32 j = 0; j < cur_bone->mNumWeights; j++)
            {
                aiVertexWeight vert_weight = cur_bone->mWeights[j];
                if (weight_count.find(vert_weight.mVertexId) == weight_count.end())
                    weight_count[vert_weight.mVertexId] = 0;

                // if (weight_count[vert_weight.mVertexId] < 4)
                //     mesh->add_weight(vert_weight.mVertexId, weight_count[vert_weight.mVertexId]++, i, vert_weight.mWeight);
            }

            //model->add_bone(current_bone);
            //mesh->bones.push_back(current_bone);
        }
    }

    std::vector<texture_wrapper> load_textures_from_material(model *mdl, aiMaterial *material, aiTextureType type, std::string texture_type)
    {
        std::vector<texture_wrapper> textures;
        for (uint32 i = 0; i < material->GetTextureCount(type); i++)
        {
            aiString str;
            material->GetTexture(type, i, &str);

            bool skip = false;
            for (uint16 j = 0; j < mdl->model_textures.size(); j++)
            {
                if (std::strcmp(mdl->model_textures[j].path.data(), str.C_Str()) == 0)
                {
                    textures.push_back(mdl->model_textures[j]);
                    skip = true;
                    break;
                }
            }

            if (!skip)
            {
                texture_wrapper texture;

                xe_graphics::graphics_device *device = xe_render::get_device();

                texture2D* texture_crt = new texture2D();
                texture_crt->desc.dimension = TEXTURE_2D;

                device->create_texture2D(str.C_Str(), mdl->parent_dir.c_str(), texture_crt);

                //texture.texture = Texture2D::create(str.C_Str(), model->parent_dir.c_str());

                texture.texture = texture_crt;
                texture.type = texture_type;
                texture.path = str.C_Str();
                textures.push_back(texture);
                mdl->model_textures.push_back(texture);
            }
        }

        return textures;
    }

    anim_node * find_node(anim_node * node, std::string & name)
    {
        if (name == node->name)
            return node;

        for (uint32 i = 0; i < node->nodes.size(); i++)
        {
            anim_node* nod = node->nodes[i];
            auto n = find_node(nod, name);
            if (n)
                return n;
        }
        return nullptr;
    }

    void parse_animations(anim_model * model, const aiScene * ai_scene)
    {
        for (uint32 i = 0; i < ai_scene->mNumAnimations; i++)
        {
            aiAnimation *ai_animation = ai_scene->mAnimations[i];

            /*Animation *anim = new Animation();

            anim->set_name(ai_animation->mName.C_Str());
            anim->set_time(ai_animation->mTicksPerSecond);
            anim->set_duration(ai_animation->mDuration);

            for (uint32 j = 0; ai_animation->mNumChannels; j++)
            {
                aiNodeAnim* ai_channel = ai_animation->mChannels[j];

                KeyFrame* frame = new KeyFrame();
                frame->name = ai_channel->mNodeName.C_Str();

                for (uint32 q = 0; q < ai_channel->mNumPositionKeys; q++)
                {
                    aiVectorKey ai_key = ai_channel->mPositionKeys[i];
                    PositionKey p_key = { ai_key.mTime, { ai_key.mValue.x,ai_key.mValue.y,ai_key.mValue.z } };
                    frame->add_position_key(p_key);
                }

                for (uint32 w = 0; w < ai_channel->mNumRotationKeys; w++)
                {
                    aiQuatKey ai_key = ai_channel->mRotationKeys[i];
                    RotationKey r_key = { ai_key.mTime,{ ai_key.mValue.w, ai_key.mValue.x,ai_key.mValue.y,ai_key.mValue.z } };
                    frame->add_rotation_key(r_key);
                }

                for (uint32 e = 0; e < ai_channel->mNumScalingKeys; e++)
                {
                    aiVectorKey ai_key = ai_channel->mScalingKeys[i];
                    PositionKey s_key = { ai_key.mTime ,{ ai_key.mValue.x,ai_key.mValue.y,ai_key.mValue.z } };
                    frame->add_scale_key(s_key);
                }

                anim->add_keyframe(frame);
            }

            model->add_animation(anim);*/
        }
    }

    void parse_materials(model * m, mesh * mesh, aiMesh * ai_mesh, const aiScene * scene)
    {
        aiMaterial* material = scene->mMaterials[ai_mesh->mMaterialIndex];

        std::vector<texture_wrapper> diffuseMaps = load_textures_from_material(m, material, aiTextureType_DIFFUSE, "tex_diff");
        for (uint16 i = 0; i < diffuseMaps.size(); i++)
            mesh->mesh_textures.push_back(diffuseMaps[i]);

        std::vector<texture_wrapper> specularMaps = load_textures_from_material(m, material, aiTextureType_SPECULAR, "tex_spec");
        for (uint16 i = 0; i < specularMaps.size(); i++)
            mesh->mesh_textures.push_back(specularMaps[i]);

        std::vector<texture_wrapper> normalMaps = load_textures_from_material(m, material, aiTextureType_HEIGHT, "tex_norm");
        for (uint16 i = 0; i < normalMaps.size(); i++)
            mesh->mesh_textures.push_back(normalMaps[i]);

        std::vector<texture_wrapper> heightMaps = load_textures_from_material(m, material, aiTextureType_AMBIENT, "tex_height");
        for (uint16 i = 0; i < normalMaps.size(); i++)
            mesh->mesh_textures.push_back(normalMaps[i]);
    }

    void mem_cpyvec(aiVector3D & aivec3, glm::vec3 & vec3)
    {
        memcpy(&vec3, &aivec3, sizeof(aivec3));
    }

    void mem_cpymatrix(aiMatrix4x4 & aimat, glm::mat4 & mat4)
    {
        memcpy(&mat4, &aimat, sizeof(aimat));
        mat4 = glm::transpose(mat4);
    }

    void calc_weight(uint32 id, real32 weight, glm::ivec4 & bone_id, glm::vec4 & wts)
    {
        for (uint16 i = 0; i < 4; i++)
        {
            if (wts[i] == 0.0f)
            {
                wts[i] = weight;
                bone_id[i] = id;
                break;
            }
        }
    }

    void parse_faces(mesh * mesh, aiMesh * aimesh)
    {
        for (uint32 i = 0; i < aimesh->mNumFaces; i++)
        {
            aiFace face = aimesh->mFaces[i];
            for (uint32 j = 0; j < face.mNumIndices; j++)
                mesh->add_index(face.mIndices[j]);
        }
    }

    bool32 create_mesh(mesh *meh)
    {
        xe_graphics::graphics_device *device = xe_render::get_device();        
        
        //device->create_vertex_array(&meh->vao);
        //device->create_vertex_buffer(meh->vertices, meh->vertices.size(), &meh->vbo);
        //device->create_index_buffer(meh->indices, meh->indices.size(), &meh->ebo);

        glGenVertexArrays(1, &meh->vao);
        glGenBuffers(1, &meh->vbo);
        glGenBuffers(1, &meh->ibo);

        glBindVertexArray(meh->vao);
        glBindBuffer(GL_ARRAY_BUFFER, meh->vbo);

        glBufferData(GL_ARRAY_BUFFER, meh->vertices.size() * sizeof(static_vertex), &meh->vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meh->ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, meh->indices.size() * sizeof(uint32), &meh->indices[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(static_vertex), (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(static_vertex), (void*)offsetof(static_vertex, normal));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(static_vertex), (void*)offsetof(static_vertex, uv));

        // @tangent & @bitangent
        //glEnableVertexAttribArray(3);
        //glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(V3F_UV2F_N3F_T3F_BI3F), (void*)offsetof(V3F_UV2F_N3F_T3F_BI3F, tangent));

        //glEnableVertexAttribArray(4);
        //glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(V3F_UV2F_N3F_T3F_BI3F), (void*)offsetof(V3F_UV2F_N3F_T3F_BI3F, bitangent));

        glBindVertexArray(0);
        glDeleteBuffers(1, &meh->vbo);
        glDeleteBuffers(1, &meh->ibo);

        return true;
    }

    model * parse_static_model(const aiScene * scene, const std::string & path)
    {
        model *mode = new model();

        mode->parent_dir = path.substr(0, path.find_last_of('/'));
        mode->root = parse_node(mode, scene->mRootNode, scene);

        //Log::info("Static model " + model->root->name + " loaded!");

        return mode;
    }

    anim_model * parse_anim_model(const aiScene * scene)
    {
        anim_model* animated_model = new anim_model();

        if (scene->HasAnimations())
            parse_animations(animated_model, scene);

        //Log::info("Animated model " + anim_model->root->name + " loaded!");

        return animated_model;
    }

    node * parse_node(model * model, aiNode * ai_node, const aiScene * scene)
    {
        node* cur_node = new node();
        cur_node->name = ai_node->mName.C_Str();

        for (uint16 i = 0; i < ai_node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[ai_node->mMeshes[i]];
            cur_node->add_mesh(parse_mesh(model, mesh, scene));
        }

        for (uint16 i = 0; i < ai_node->mNumChildren; i++)
        {
            cur_node->add_child(parse_node(model, ai_node->mChildren[i], scene));
        }

        return cur_node;
    }

    mesh * parse_mesh(model * model, aiMesh * ai_mesh, const aiScene * scene)
    {
        mesh* mes = new mesh();
        parse_vert(mes, ai_mesh);
        parse_faces(mes, ai_mesh);
        parse_materials(model, mes, ai_mesh, scene);

        create_mesh(mes);

        return mes;
    }

    model* xe_assets::load_model_from_file(const std::string &path)
    {
        Assimp::Importer importer;
        // @FLip UV ???
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_CalcTangentSpace);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            xe_utility::error(importer.GetErrorString());
            return nullptr;
        }

        model *result = parse_static_model(scene, path);

        if(result)
            xe_utility::info("Model " + result->root->name + " was loaded!");
        else
            xe_utility::error("Loading of model " + result->root->name + " was failed!");

        return result;
    }

    anim_model * load_anim_model_from_file(const std::string &path)
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_CalcTangentSpace);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            xe_utility::error(importer.GetErrorString());
            return nullptr;
        }

        anim_model *result = parse_anim_model(scene);

        return result;
    }


    void parse_vert(mesh *meh, aiMesh *aimesh)
    {
        std::vector<static_vertex> vertices;
        std::vector<uint32> indices;
        std::vector<texture_wrapper> textures;

        for (uint32 i = 0; i < aimesh->mNumVertices; i++)
        {
            static_vertex vertex;
            vec3f vector;

            if (aimesh->HasPositions())
            {
                // @SpeedUp: memcpy above
                vector.x = aimesh->mVertices[i].x;
                vector.y = aimesh->mVertices[i].y;
                vector.z = aimesh->mVertices[i].z;
                vertex.pos = vector;
            }

            if (aimesh->HasNormals())
            {
                vector.x = aimesh->mNormals[i].x;
                vector.y = aimesh->mNormals[i].y;
                vector.z = aimesh->mNormals[i].z;
                vertex.normal = vector;
            }

            if (aimesh->HasTextureCoords(0))
            {
                vec2f uv;

                uv.x = aimesh->mTextureCoords[0][i].x;
                uv.y = aimesh->mTextureCoords[0][i].y;

                vertex.uv = uv;
            }
            else
                vertex.uv = vec2f(0.0f, 0.0f);

            // @Note : not using tbn right now
            /*if (aimesh->HasTangentsAndBitangents())
            {
                vector.x = aimesh->mTangents[i].x;
                vector.y = aimesh->mTangents[i].y;
                vector.z = aimesh->mTangents[i].z;
                //vertex.tangent = vector;

                vector.x = aimesh->mBitangents[i].x;
                vector.y = aimesh->mBitangents[i].y;
                vector.z = aimesh->mBitangents[i].z;
                //vertex.bitangent = vector;
            }*/

            meh->add_vertex(vertex);
        }
    }

    void mesh::add_vertex(static_vertex vertex)
    {
        vertices.push_back(vertex);
    }

    void mesh::add_index(uint32 ind)
    {
        indices.push_back(ind);
    }

    void node::add_child(node *child)
    {
        children.push_back(child);
    }

    void node::add_mesh(mesh *msh)
    {
        meshes.push_back(msh);
    }
}