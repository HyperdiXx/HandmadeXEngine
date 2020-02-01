#include "model_loader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <runtime/geometry/model.h>
#include <rendering/api/base/texture2D.h>

#include <runtime/animation/animation.h>
#include <runtime/animation/key_frame.h>

namespace XEngine
{
    glm::mat4 transposeAiMat4(aiMatrix4x4 ai_mat) 
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

    void parse_bones(Assets::AnimatedModel *model, Assets::AnimatedMesh *mesh, aiMesh *ai_mesh)
    {
        using namespace Assets;
        std::unordered_map<uint32, uint32> weight_count;

        for (uint32 i = 0; i < ai_mesh->mNumBones; i++)
        {
            aiBone* cur_bone = ai_mesh->mBones[i];
 
            std::shared_ptr<Bone> bone{ new Bone{cur_bone->mName.C_Str(), transposeAiMat4(cur_bone->mOffsetMatrix)} };

            for (uint32 j = 0; j < cur_bone->mNumWeights; j++)
            {
                aiVertexWeight vert_weight = cur_bone->mWeights[j];
                if (weight_count.find(vert_weight.mVertexId) == weight_count.end())
                    weight_count[vert_weight.mVertexId] = 0;

                if (weight_count[vert_weight.mVertexId] < 4) 
                    mesh->add_weight(vert_weight.mVertexId, weight_count[vert_weight.mVertexId]++, i, vert_weight.mWeight);
            }

            model->add_bone(bone);
            mesh->bones.push_back(bone);
        }        
    }

    std::vector<Assets::TextureWrapper> load_textures_from_material(Assets::Model *model, aiMaterial *material, aiTextureType type, std::string texture_type)
    {
        using namespace Assets;
        using namespace Rendering;

        std::vector<TextureWrapper> textures;
        for (uint32 i = 0; i < material->GetTextureCount(type); i++)
        {
            aiString str;
            material->GetTexture(type, i, &str);
            
            bool skip = false;
            for (uint16 j = 0; j < model->model_textures.size(); j++)
            {
                if (std::strcmp(model->model_textures[j].path.data(), str.C_Str()) == 0)
                {
                    textures.push_back(model->model_textures[j]);
                    skip = true; 
                    break;
                }
            }

            if (!skip)
            {   
                TextureWrapper texture;
                texture.texture = Texture2D::create(str.C_Str(), model->parent_dir.c_str());
                texture.type = texture_type;
                texture.path = str.C_Str();
                textures.push_back(texture);
                model->model_textures.push_back(texture);  
            }
        }
        return textures;
    }

    Assets::AnimNode *find_node(Assets::AnimNode*node, std::string &name)
    {
        if(name == node->name)
            return node;

        for (uint32 i = 0; i < node->nodes.size(); i++)
        {
            using namespace Assets;
            AnimNode* nod = node->nodes[i];
            auto n = find_node(nod, name);
            if(n)
                return n;
        }
        return nullptr;
    }

    void parse_animations(Assets::AnimatedModel *model, const aiScene *ai_scene)
    {
        for (uint32 i = 0; i < ai_scene->mNumAnimations; i++)
        {
            aiAnimation *ai_animation = ai_scene->mAnimations[i];

            Animation *anim = new Animation();

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
            
            model->add_animation(anim);
        }
    }

    void parse_materials(Assets::Model *model, Assets::Mesh *mesh, aiMesh* ai_mesh, const aiScene *scene)
    {
        using namespace Assets;
        aiMaterial* material = scene->mMaterials[ai_mesh->mMaterialIndex];
        
        std::vector<TextureWrapper> diffuseMaps = load_textures_from_material(model, material, aiTextureType_DIFFUSE, "tex_diff");             
        for(uint16 i = 0; i < diffuseMaps.size(); i++)
            mesh->mesh_textures.push_back(diffuseMaps[i]);

        std::vector<TextureWrapper> specularMaps = load_textures_from_material(model, material, aiTextureType_SPECULAR, "tex_spec");
        for (uint16 i = 0; i < specularMaps.size(); i++)
            mesh->mesh_textures.push_back(specularMaps[i]);

        std::vector<TextureWrapper> normalMaps = load_textures_from_material(model, material, aiTextureType_HEIGHT, "tex_norm");
        for (uint16 i = 0; i < normalMaps.size(); i++)
            mesh->mesh_textures.push_back(normalMaps[i]);
        
        std::vector<TextureWrapper> heightMaps = load_textures_from_material(model, material, aiTextureType_AMBIENT, "tex_height");
        for (uint16 i = 0; i < normalMaps.size(); i++)
            mesh->mesh_textures.push_back(normalMaps[i]);
    }

    void mem_cpyvec(aiVector3D & aivec3, glm::vec3 &vec3)
    {
        memcpy(&vec3, &aivec3, sizeof(aivec3));
    }

    void mem_cpymatrix(aiMatrix4x4 & aimat, glm::mat4 &mat4)
    {
        memcpy(&mat4, &aimat, sizeof(aimat));
        mat4 = glm::transpose(mat4);
    }

    void calc_weight(uint32 id, real32 weight, glm::ivec4& bone_id, glm::vec4& wts)
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

    void parse_vert(Assets::Mesh* mesh, aiMesh *aimesh)
    {
        using namespace Assets;

        std::vector<StaticVertex> vertices;
        std::vector<uint32> indices;
        std::vector<TextureWrapper> textures;

        for (uint32 i = 0; i < aimesh->mNumVertices; i++)
        {
            StaticVertex vertex;
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

            mesh->add_vertex(vertex);
        }
    }

    void parse_faces(Assets::Mesh* mesh, aiMesh *aimesh)
    {
        for (uint32 i = 0; i < aimesh->mNumFaces; i++)
        {
            aiFace face = aimesh->mFaces[i];
            for (uint32 j = 0; j < face.mNumIndices; j++)
                mesh->add_index(face.mIndices[j]);
        }
    }

    Assets::Mesh* parse_mesh(Assets::Model *model, aiMesh* ai_mesh, const aiScene *scene)
    {
        using namespace XEngine::Assets;

        Mesh* mesh = new Mesh();
        parse_vert(mesh, ai_mesh);
        parse_faces(mesh, ai_mesh);
        parse_materials(model, mesh, ai_mesh, scene);
        mesh->setup_mesh();

        return mesh;
    }

    Assets::Node* parse_node(Assets::Model* model, aiNode* ai_node, const aiScene *scene)
    {
        using namespace Assets;

        Node* cur_node = new Node();
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

    Assets::Model* parse_static_model(const aiScene* scene, const std::string &path)
    {
        Assets::Model *model = new Assets::Model();

        model->parent_dir = path.substr(0, path.find_last_of('/'));
        model->root = parse_node(model, scene->mRootNode, scene);

        Log::info("Static model " + model->root->name + " loaded!");
        
        return model;
    }

    Assets::AnimatedModel *parse_anim_model(const aiScene* scene)
    {
        Assets::AnimatedModel* anim_model = new Assets::AnimatedModel();

        if (scene->HasAnimations())
            parse_animations(anim_model, scene);
                                    
        Log::info("Animated model " + anim_model->root->name + " loaded!");

        return anim_model;
    }

    Assets::Model* ModelLoader::load_model_from_file(const std::string const & path)
    {
        using namespace XEngine::Assets;

        Assimp::Importer importer;
        // @FLip UV ???
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_CalcTangentSpace);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            Log::error(importer.GetErrorString());
            return nullptr;
        }

        Assets::Model *result = parse_static_model(scene, path);
        
        return result;
    }

    Assets::AnimatedModel * ModelLoader::load_anim_model_from_file(const std::string const & path)
    {
        using namespace XEngine::Assets;

        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_CalcTangentSpace);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            Log::error(importer.GetErrorString());
            return nullptr;
        }

        Assets::AnimatedModel*result = parse_anim_model(scene);

        return result;
    }
};
