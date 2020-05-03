#include "xe_assets.h"

#include "xe_utility.h"

#include <glad/glad.h>

namespace xe_assets
{
    static bool32 calculate_tspace;

    glm::mat4 xe_assets::from_ai_to_glm(const aiMatrix4x4 &ai_mat)
    {
        glm::mat4 res;

        res[0][0] = ai_mat.a1;  
        res[0][1] = ai_mat.b1;
        res[0][2] = ai_mat.c1;
        res[0][3] = ai_mat.d1;

        res[1][0] = ai_mat.a2;
        res[1][1] = ai_mat.b2;
        res[1][2] = ai_mat.c2;
        res[1][3] = ai_mat.d2;

        res[2][0] = ai_mat.a3;
        res[2][1] = ai_mat.b3;
        res[2][2] = ai_mat.c3;
        res[2][3] = ai_mat.d3;

        res[3][0] = ai_mat.a4;
        res[3][1] = ai_mat.b4;
        res[3][2] = ai_mat.c4;
        res[3][3] = ai_mat.d4;

        return res;
    }

    void parse_bones(anim_model *animmodel, anim_mesh *mesh, aiMesh *ai_mesh)
    {
        std::unordered_map<uint32, uint32> weight_count;

        for (uint32 i = 0; i < ai_mesh->mNumBones; i++)
        {
            aiBone* cur_bone = ai_mesh->mBones[i];

            std::shared_ptr<bone> current_bone{ new bone{cur_bone->mName.C_Str(), from_ai_to_glm(cur_bone->mOffsetMatrix)} };

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

    vertex *get_vertex_type(model *mdl)
    {        
        return mdl->vertex_type;
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

    void parse_materials(model *m, mesh *mesh, aiMesh *ai_mesh, const aiScene *scene)
    {
        aiMaterial* material = scene->mMaterials[ai_mesh->mMaterialIndex];

        std::vector<texture_wrapper> diffuseMaps = load_textures_from_material(m, material, aiTextureType_DIFFUSE, "tex_diff");
        for (uint16 i = 0; i < diffuseMaps.size(); i++)
            mesh->mesh_textures.push_back(diffuseMaps[i]);

        std::vector<texture_wrapper> specularMaps = load_textures_from_material(m, material, aiTextureType_SPECULAR, "tex_spec");
        for (uint16 i = 0; i < specularMaps.size(); i++)
            mesh->mesh_textures.push_back(specularMaps[i]);

        std::vector<texture_wrapper> normalMaps = load_textures_from_material(m, material, aiTextureType_NORMALS, "tex_norm");
        for (uint16 i = 0; i < normalMaps.size(); i++)
            mesh->mesh_textures.push_back(normalMaps[i]);

        std::vector<texture_wrapper> height_tex = load_textures_from_material(m, material, aiTextureType_HEIGHT, "tex_height");
        for (uint16 i = 0; i < height_tex.size(); i++)
            mesh->mesh_textures.push_back(height_tex[i]);

        // pbr rough
        std::vector<texture_wrapper> roughness_tex = load_textures_from_material(m, material, aiTextureType_SHININESS, "tex_roughness");
        for (uint16 i = 0; i < roughness_tex.size(); i++)
            mesh->mesh_textures.push_back(roughness_tex[i]);
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

    model *parse_static_model(const aiScene *scene, const std::string &path)
    {
        model *mode = new model();

        if (calculate_tspace)
            mode->vertex_type = new pos_normal_tb_uv();
        else
            mode->vertex_type = new pos_normal_uv();
        
        mode->parent_dir = path.substr(0, path.find_last_of('/'));
        mode->root = parse_node(mode, scene->mRootNode, scene);

        //Log::info("Static model " + model->root->name + " loaded!");

        return mode;
    }

    anim_model *parse_anim_model(const aiScene *scene)
    {
        anim_model* animated_model = new anim_model();

        if (scene->HasAnimations())
            parse_animations(animated_model, scene);

        //Log::info("Animated model " + anim_model->root->name + " loaded!");

        return animated_model;
    }

    node *parse_node(model * model, aiNode * ai_node, const aiScene * scene)
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

    mesh *parse_mesh(model *model, aiMesh *ai_mesh, const aiScene *scene)
    {
        mesh* mes = new mesh();
        
        parse_vert(mes, ai_mesh);
        parse_faces(mes, ai_mesh);
        parse_materials(model, mes, ai_mesh, scene);

        xe_render::create_mesh(mes, model->vertex_type, calculate_tspace);

        return mes;
    }

    model* xe_assets::load_model_from_file(const std::string &path, bool32 calculate_tb)
    {
        Assimp::Importer importer;

        // @FLip UV ???
        uint32 flags = aiProcess_Triangulate;

        if (calculate_tb)
        {
            flags |= aiProcess_CalcTangentSpace;            
        }

        const aiScene* scene = importer.ReadFile(path, flags);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            xe_utility::error(importer.GetErrorString());
            return nullptr;
        }

        calculate_tspace = calculate_tb;
        
        model *result = parse_static_model(scene, path);

        if(result)
            xe_utility::info("Model " + result->root->name + " was loaded!");
        else
            xe_utility::error("Loading of model " + result->root->name + " was failed!");

        return result;
    }

    anim_model *load_anim_model_from_file(const std::string &path, bool32 calculate_tb)
    {
        Assimp::Importer importer;

        uint32 flags = aiProcess_Triangulate;

        if (calculate_tb)
            flags |= aiProcess_CalcTangentSpace;

        const aiScene* scene = importer.ReadFile(path, flags);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            xe_utility::error(importer.GetErrorString());
            return nullptr;
        }

        calculate_tspace = calculate_tb;

        anim_model *result = parse_anim_model(scene);

        return result;
    }


    void parse_vert(mesh *meh, aiMesh *aimesh)
    {
        meh->vertices_fl.reserve(aimesh->mNumVertices);
        
        meh->bounding_box.min = glm::vec3(FLT_MAX, FLT_MAX, FLT_MAX);
        meh->bounding_box.max = glm::vec3(-FLT_MAX, -FLT_MAX, -FLT_MAX);

        glm::vec3 pos;

        for (uint32 i = 0; i < aimesh->mNumVertices; i++)
        {
            if (aimesh->HasPositions())
            {
                // @SpeedUp: memcpy above
                meh->vertices_fl.push_back(aimesh->mVertices[i].x);
                meh->vertices_fl.push_back(aimesh->mVertices[i].y);
                meh->vertices_fl.push_back(aimesh->mVertices[i].z);

                pos.x = aimesh->mVertices[i].x;
                pos.y = aimesh->mVertices[i].y;
                pos.z = aimesh->mVertices[i].z;

                meh->bounding_box.min.x = glm::min(pos.x, meh->bounding_box.min.x);
                meh->bounding_box.min.y = glm::min(pos.y, meh->bounding_box.min.y);
                meh->bounding_box.min.z = glm::min(pos.z, meh->bounding_box.min.z);

                meh->bounding_box.max.x = glm::max(pos.x, meh->bounding_box.max.x);
                meh->bounding_box.max.y = glm::max(pos.y, meh->bounding_box.max.y);
                meh->bounding_box.max.z = glm::max(pos.z, meh->bounding_box.max.z);
            }

            if (aimesh->HasNormals())
            {
                meh->vertices_fl.push_back(aimesh->mNormals[i].x);
                meh->vertices_fl.push_back(aimesh->mNormals[i].y);
                meh->vertices_fl.push_back(aimesh->mNormals[i].z);
            }

            if (aimesh->HasTangentsAndBitangents())
            {
                meh->vertices_fl.push_back(aimesh->mTangents[i].x);
                meh->vertices_fl.push_back(aimesh->mTangents[i].y);
                meh->vertices_fl.push_back(aimesh->mTangents[i].z);

                meh->vertices_fl.push_back(aimesh->mBitangents[i].x);
                meh->vertices_fl.push_back(aimesh->mBitangents[i].y);
                meh->vertices_fl.push_back(aimesh->mBitangents[i].z);
            }

            if (aimesh->HasTextureCoords(0))
            {
                meh->vertices_fl.push_back(aimesh->mTextureCoords[0][i].x);
                meh->vertices_fl.push_back(aimesh->mTextureCoords[0][i].y);
            }
            else
            {
                meh->vertices_fl.push_back(0.0f);
                meh->vertices_fl.push_back(0.0f);
            }
        }
    }

    void mesh::add_vertex(pos_normal_uv vertex)
    {
        vertices.push_back(vertex);
    }

    void mesh::add_vertex(pos_normal_tb_uv vertex)
    {
        vertices_tab.push_back(vertex);
    }

    void mesh::add_vertex(real32 vertex)
    {
        vertices_fl.push_back(vertex);
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