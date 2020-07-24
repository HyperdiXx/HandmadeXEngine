#include "xe_assets.h"

#include "xe_utility.h"

#include <glad/glad.h>

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>

namespace xe_assets
{
    static bool32 calculate_tspace;

    glm::mat4 xe_assets::fromAiToGlm(const aiMatrix4x4 &ai_mat)
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

    std::vector<TextureWrapper> loadTexturesFromMaterial(Model *mdl, aiMaterial *material, aiTextureType type, std::string texture_type)
    {
        std::vector<TextureWrapper> textures;
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
                TextureWrapper texture;

                xe_graphics::GraphicsDevice *device = xe_render::getDevice();

                Texture2D* texture_crt = new Texture2D();
                texture_crt->desc.dimension = TEXTURE_2D;

                device->createTexture2D(str.C_Str(), mdl->parent_dir.c_str(), texture_crt);

                texture.texture = texture_crt;
                texture.type = texture_type;
                texture.path = str.C_Str();
                textures.push_back(texture);
                mdl->model_textures.push_back(texture);
            }
        }

        return textures;
    }

    Vertex *getVertexType(Model *mdl)
    {        
        return mdl->vertex_type;
    }

    /*void parse_animations(anim_model * model, const aiScene * ai_scene)
    {
        for (uint32 i = 0; i < ai_scene->mNumAnimations; i++)
        {
            aiAnimation *ai_animation = ai_scene->mAnimations[i];

            animation anim = {};

            anim.name = ai_animation->mName.C_Str();
            anim.ticks_per_second = ai_animation->mTicksPerSecond;
            anim.duration = ai_animation->mDuration;

            for (uint32 j = 0; ai_animation->mNumChannels; j++)
            {
                aiNodeAnim* ai_channel = ai_animation->mChannels[j];

                //KeyFrame* frame = new KeyFrame();
                //frame->name = ai_channel->mNodeName.C_Str();

                for (uint32 q = 0; q < ai_channel->mNumPositionKeys; q++)
                {
                    aiVectorKey ai_key = ai_channel->mPositionKeys[i];
                    //PositionKey p_key = { ai_key.mTime, { ai_key.mValue.x,ai_key.mValue.y,ai_key.mValue.z } };
                    //frame->add_position_key(p_key);
                }

                for (uint32 w = 0; w < ai_channel->mNumRotationKeys; w++)
                {
                    aiQuatKey ai_key = ai_channel->mRotationKeys[i];
                    //RotationKey r_key = { ai_key.mTime,{ ai_key.mValue.w, ai_key.mValue.x,ai_key.mValue.y,ai_key.mValue.z } };
                    //frame->add_rotation_key(r_key);
                }

                for (uint32 e = 0; e < ai_channel->mNumScalingKeys; e++)
                {
                    aiVectorKey ai_key = ai_channel->mScalingKeys[i];
                    //PositionKey s_key = { ai_key.mTime ,{ ai_key.mValue.x,ai_key.mValue.y,ai_key.mValue.z } };
                    //frame->add_scale_key(s_key);
                }

                //anim->add_keyframe(frame);
            }

            model->animations.push_back(anim);
        }
    }*/

    void parseMaterials(Model *m, Mesh *mesh, aiMesh *ai_mesh, const aiScene *scene)
    {
        aiMaterial* material = scene->mMaterials[ai_mesh->mMaterialIndex];

        std::vector<TextureWrapper> diffuseMaps = loadTexturesFromMaterial(m, material, aiTextureType_DIFFUSE, "tex_diff");
        for (uint16 i = 0; i < diffuseMaps.size(); i++)
            mesh->mesh_textures.push_back(diffuseMaps[i]);

        std::vector<TextureWrapper> specularMaps = loadTexturesFromMaterial(m, material, aiTextureType_SPECULAR, "tex_spec");
        for (uint16 i = 0; i < specularMaps.size(); i++)
            mesh->mesh_textures.push_back(specularMaps[i]);

        std::vector<TextureWrapper> normalMaps = loadTexturesFromMaterial(m, material, aiTextureType_NORMALS, "tex_norm");
        for (uint16 i = 0; i < normalMaps.size(); i++)
            mesh->mesh_textures.push_back(normalMaps[i]);

        std::vector<TextureWrapper> height_tex = loadTexturesFromMaterial(m, material, aiTextureType_HEIGHT, "tex_height");
        for (uint16 i = 0; i < height_tex.size(); i++)
            mesh->mesh_textures.push_back(height_tex[i]);

        // pbr rough
        std::vector<TextureWrapper> roughness_tex = loadTexturesFromMaterial(m, material, aiTextureType_SHININESS, "tex_roughness");
        for (uint16 i = 0; i < roughness_tex.size(); i++)
            mesh->mesh_textures.push_back(roughness_tex[i]);
    }

    void memCpyvec(aiVector3D &aivec3, glm::vec3 &vec3)
    {
        memcpy(&vec3, &aivec3, sizeof(aivec3));
    }

    void memCpymatrix(aiMatrix4x4 & aimat, glm::mat4 &mat4)
    {
        memcpy(&mat4, &aimat, sizeof(aimat));
        mat4 = glm::transpose(mat4);
    }

    void calcWeight(uint32 id, real32 weight, glm::ivec4 &bone_id, glm::vec4 &wts)
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

    void parseFaces(Mesh *mesh, aiMesh *aimesh)
    {        
        for (uint32 i = 0; i < aimesh->mNumFaces; i++)
        {
            aiFace face = aimesh->mFaces[i];

            for (uint32 j = 0; j < face.mNumIndices; j++)
            {
                mesh->addIndex(face.mIndices[j]);
                
            }
        }
    }

    Model *parseStaticModel(const aiScene *scene, const std::string &path)
    {
        Model *mode = new Model();

        if (calculate_tspace)
        {
            mode->vertex_type = new PositionNormalTBUV();
        }
        else
        {
            mode->vertex_type = new PositionNormalUV();
        }

        mode->parent_dir = path.substr(0, path.find_last_of('/'));
        mode->root = parseNode(mode, scene->mRootNode, scene);

        //Log::info("Static model " + model->root->name + " loaded!");

        return mode;
    }

    Node *parseNode(Model *model, aiNode *ai_node, const aiScene *scene)
    {
        Node* cur_node = new Node();
        cur_node->name = ai_node->mName.C_Str();

        for (uint16 i = 0; i < ai_node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[ai_node->mMeshes[i]];
            cur_node->addMesh(parseMesh(model, mesh, scene));
        }

        for (uint16 i = 0; i < ai_node->mNumChildren; i++)
        {
            cur_node->addChild(parseNode(model, ai_node->mChildren[i], scene));
        }

        return cur_node;
    }

    Mesh *parseMesh(Model *model, aiMesh *ai_mesh, const aiScene *scene)
    {
        Mesh* mes = new Mesh();
        
        parseVert(mes, ai_mesh);
        parseFaces(mes, ai_mesh);
        parseMaterials(model, mes, ai_mesh, scene);

        xe_render::createMesh(mes, model->vertex_type, calculate_tspace);

        return mes;
    }

    Model* xe_assets::loadModelFromFile(const std::string &path, bool32 calculate_tb)
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
        
        Model *result = parseStaticModel(scene, path);

        if(result)
            xe_utility::info("Model " + result->root->name + " was loaded!");
        else
            xe_utility::error("Loading of model " + result->root->name + " was failed!");

        return result;
    }

    void parseVert(Mesh *meh, aiMesh *aimesh)
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

    void Mesh::addVertex(PositionNormalUV vertex)
    {
        vertices.push_back(vertex);
    }

    void Mesh::addVertex(PositionNormalTBUV vertex)
    {
        vertices_tab.push_back(vertex);
    }

    void Mesh::addVertex(real32 vertex)
    {
        vertices_fl.push_back(vertex);
    }

    void Mesh::addIndex(uint32 ind)
    {
        indices.push_back(ind);
    }

    void Node::addChild(Node *child)
    {
        children.push_back(child);
    }

    void Node::addMesh(Mesh *msh)
    {
        meshes.push_back(msh);
    }

    AnimModel::AnimModel(const std::string &path)
    {
        static const uint32_t import_flags =
            aiProcess_CalcTangentSpace |        // Create binormals/tangents just in case
            aiProcess_Triangulate |             // Make sure we're triangles
            aiProcess_SortByPType |             // Split meshes by primitive type
            aiProcess_GenNormals |              // Make sure we have legit normals
            aiProcess_GenUVCoords |             // Convert UVs if required 
            aiProcess_OptimizeMeshes |          // Batch draws where possible
            aiProcess_ValidateDataStructure;    // Validation

        assimp_importer = std::make_unique<Assimp::Importer>();

        scene = assimp_importer->ReadFile(path.c_str(), import_flags);
        bool isAnimationsLoaded = scene->mAnimations != nullptr;
        global_inverse_transform = glm::inverse(fromAiToGlm(scene->mRootNode->mTransformation));

        uint32_t vertexCount = 0;
        uint32_t indexCount = 0;

        anim_meshes.reserve(scene->mNumMeshes);
         
        for (size_t i = 0; i < scene->mNumMeshes; ++i)
        {
            aiMesh *mesh = scene->mMeshes[i];

            AnimNode anim_mesh = {};
            anim_mesh.start_vertex = vertexCount;
            anim_mesh.start_index = indexCount;
            anim_mesh.index_count = mesh->mNumFaces * 3;
            anim_mesh.material_index = mesh->mMaterialIndex;
            anim_meshes.push_back(anim_mesh);

            vertexCount += mesh->mNumVertices;
            indexCount += anim_mesh.index_count;

            
            for (size_t i = 0; i < mesh->mNumVertices; i++)
            {
                PositionNormalUVBW vertex;
                vertex.pos = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
                vertex.normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };

                if (mesh->HasTangentsAndBitangents())
                {
                    vertex.tangent = { mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z };
                    vertex.bitangent = { mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z };
                }

                if (mesh->HasTextureCoords(0))
                    vertex.uv = { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };

                anim_vertices.push_back(vertex);
            }

            for (size_t i = 0; i < mesh->mNumFaces; i++)
            {
                aiFace face = mesh->mFaces[i];
                for (uint32 j = 0; j < face.mNumIndices; j++)
                    anim_indices.push_back(face.mIndices[j]);
            }

            updateNodeTransform(scene->mRootNode);

            for (size_t m = 0; m < scene->mNumMeshes; m++)
            {
                aiMesh* mesh = scene->mMeshes[m];
                AnimNode& node = anim_meshes[m];

                for (size_t i = 0; i < mesh->mNumBones; i++)
                {
                    aiBone* bone_loader = mesh->mBones[i];
                    std::string boneName(bone_loader->mName.data);
                    int boneIndex = 0;

                    if (bones_map.find(boneName) == bones_map.end())
                    {
                        boneIndex = bones_count;
                        bones_count++;
                        Bone bi;
                        bones_info.push_back(bi);
                        bones_info[boneIndex].offset = fromAiToGlm(bone_loader->mOffsetMatrix);
                        bones_map[boneName] = boneIndex;
                    }
                    else
                    {
                        boneIndex = bones_map[boneName];
                    }

                    for (size_t j = 0; j < bone_loader->mNumWeights; j++)
                    {
                        int vertexID = node.start_vertex + bone_loader->mWeights[j].mVertexId;
                        float weight = bone_loader->mWeights[j].mWeight;
                        anim_vertices[vertexID].addBone(boneIndex, weight);
                    }
                }
            }
        }

        // GPU data creation

        GraphicsDevice *device = xe_render::getDevice();

        va.buffers.push_back(new xe_graphics::VertexBuffer);        
        va.ib = new xe_graphics::IndexBuffer;
        
        device->createVertexArray(&va);
        device->bindVertexArray(&va);
        device->createVertexBuffer(anim_vertices.data(), anim_vertices.size() * sizeof(PositionNormalUVBW), DRAW_TYPE::STATIC, va.buffers[0]);
        device->createIndexBuffer(anim_indices.data(), anim_indices.size(), va.ib);

        using namespace xe_graphics;

        BufferLayout buffer_layout = {};

        std::initializer_list<xe_graphics::BufferElement> init_list =
        {
            { "aPos",         ElementType::Float3, },
            { "aNormal",      ElementType::Float3, },
            { "aTangent",     ElementType::Float3, },
            { "aBitangent",   ElementType::Float3, },
            { "aUV",          ElementType::Float2, },          
            { "aBoneIDs",     ElementType::Int4, },
            { "aBoneWeights", ElementType::Float4, }
        };

        device->createBufferLayout(init_list, &buffer_layout);
        device->setVertexBufferLayout(va.buffers[0], &buffer_layout);
        device->addVertexBuffer(&va, va.buffers[0]);
        device->setIndexBuffer(&va, va.ib);
    }

    Model::Model(Model && m)
    {
        root = m.root;
        vertex_type = m.vertex_type;
        parent_dir = std::move(m.parent_dir);
        model_textures = std::move(m.model_textures);
        nodes = std::move(m.nodes);
    }

    Model &Model::operator=(Model && m) noexcept
    {
        root = m.root;
        vertex_type = m.vertex_type;
        parent_dir = std::move(m.parent_dir);
        model_textures = std::move(m.model_textures);
        nodes = std::move(m.nodes);
        return *this;
    }

    AnimModel::AnimModel(AnimModel && m)
    {
        activeAnimation = m.activeAnimation;
        global_inverse_transform = std::move(m.global_inverse_transform);

        assimp_importer = std::move(m.assimp_importer);;
        scene = m.scene;

        anim_meshes = std::move(m.anim_meshes);
        bones_map = std::move(m.bones_map);
        bones_info = std::move(m.bones_info);

        anim_vertices = std::move(m.anim_vertices);
        anim_indices = std::move(m.anim_indices);
        bone_transformation = std::move(m.bone_transformation);

        bones_count = m.bones_count;
        animation_speed = m.animation_speed;
        animation_time = m.animation_time;

        va = std::move(m.va);
    }

    AnimModel &AnimModel::operator=(AnimModel && m) noexcept
    {
        activeAnimation = m.activeAnimation;
        global_inverse_transform = std::move(m.global_inverse_transform);

        assimp_importer = std::move(m.assimp_importer);;
        scene = m.scene;

        anim_meshes = std::move(m.anim_meshes);
        bones_map = std::move(m.bones_map);
        bones_info = std::move(m.bones_info);

        anim_vertices = std::move(m.anim_vertices);
        anim_indices = std::move(m.anim_indices);
        bone_transformation = std::move(m.bone_transformation);

        bones_count = m.bones_count;
        animation_speed = m.animation_speed;
        animation_time = m.animation_time;

        va = std::move(m.va);
        return *this;
    }
    
    void AnimModel::update(float dt)
    {
        if (activeAnimation)
        {
            float ticks_per_second = (float)(activeAnimation->mTicksPerSecond != 0 ? activeAnimation->mTicksPerSecond : 25.0f);
            animation_time += dt * ticks_per_second;
            animation_time = fmod(animation_time, (float)activeAnimation->mDuration);

            transformBones(animation_time);
        }        
    }

    const aiNodeAnim *AnimModel::findAnimNodeByName(const aiAnimation *animation, const std::string &node_name)
    {
        for (uint32_t i = 0; i < animation->mNumChannels; i++)
        {
            const aiNodeAnim* nodeAnim = animation->mChannels[i];
            if (std::string(nodeAnim->mNodeName.data) == node_name)
            {
                return nodeAnim;
            }
        }

        return nullptr;
    }

    uint32_t AnimModel::getTranslationIndexForNode(float anim_time, const aiNodeAnim *node_anim)
    {
        for (uint32_t i = 0; i < node_anim->mNumPositionKeys - 1; i++)
        {
            if (anim_time < (float)node_anim->mPositionKeys[i + 1].mTime)
                return i;
        }

        return 0;
    }

    uint32_t AnimModel::getRotationIndexForNode(float anim_time, const aiNodeAnim *node_anim)
    {        
        for (uint32_t i = 0; i < node_anim->mNumRotationKeys - 1; i++)
        {
            if (anim_time < (float)node_anim->mRotationKeys[i + 1].mTime)
                return i;
        }

        return 0;
    }

    uint32_t AnimModel::getScaleIndexForNode(float anim_time, const aiNodeAnim *node_anim)
    {
        for (uint32_t i = 0; i < node_anim->mNumScalingKeys - 1; i++)
        {
            if (anim_time < (float)node_anim->mScalingKeys[i + 1].mTime)
                return i;
        }

        return 0;
    }

    glm::vec3 AnimModel::getTranslationBetweenFrames(float dt, const aiNodeAnim *na)
    {
        glm::vec3 translation = glm::vec3();
        
        if (na->mNumPositionKeys == 1)
        {
            auto res = na->mPositionKeys[0].mValue;
            translation.x = res.x;
            translation.y = res.y;
            translation.z = res.z;

            return translation;
        }      
        
        uint32_t index_frame = getTranslationIndexForNode(dt, na);
        
        uint32_t next_pos_index_frame = index_frame + 1;

        float deltaTime = (float)(na->mPositionKeys[next_pos_index_frame].mTime - na->mPositionKeys[index_frame].mTime);
        float Factor = (dt - (float)na->mPositionKeys[index_frame].mTime) / deltaTime;
        if (Factor < 0.0f)
            Factor = 0.0f;

        aiVectorKey currentFrame = na->mPositionKeys[index_frame];
        aiVectorKey nextFrame = na->mPositionKeys[next_pos_index_frame];

        const aiVector3D& start = currentFrame.mValue;
        const aiVector3D& end = nextFrame.mValue;
        aiVector3D delta = end - start;

        auto aiVec = (start + Factor * delta);
        
        translation.x = aiVec.x;
        translation.y = aiVec.y;
        translation.z = aiVec.z;

        return translation;
    }

    glm::quat AnimModel::getRotationBetweenFrames(float dt, const aiNodeAnim *na)
    {
        if (na->mNumRotationKeys == 1)
        {
            auto v = na->mRotationKeys[0].mValue;
            return glm::quat(v.w, v.x, v.y, v.z);
        }

        uint32_t RotationIndex = getRotationIndexForNode(dt, na);
        uint32_t NextRotationIndex = (RotationIndex + 1);
        
        float DeltaTime = (float)(na->mRotationKeys[NextRotationIndex].mTime - na->mRotationKeys[RotationIndex].mTime);
        float Factor = (dt - (float)na->mRotationKeys[RotationIndex].mTime) / DeltaTime;
        if (Factor < 0.0f)
            Factor = 0.0f;
        
        const aiQuaternion& StartRotationQ = na->mRotationKeys[RotationIndex].mValue;
        const aiQuaternion& EndRotationQ = na->mRotationKeys[NextRotationIndex].mValue;
        auto q = aiQuaternion();
        
        aiQuaternion::Interpolate(q, StartRotationQ, EndRotationQ, Factor);
        q = q.Normalize();
        return glm::quat(q.w, q.x, q.y, q.z);
    }

    glm::vec3 AnimModel::getScaleBetweenFrames(float dt, const aiNodeAnim *na)
    {
        glm::vec3 scale;
       
        if (na->mNumScalingKeys == 1)
        {
            auto scl = na->mScalingKeys[0].mValue;
            scale.x = scl.x;
            scale.y = scl.y;
            scale.z = scl.z;

            return scale;
        }

        uint32_t index = getScaleIndexForNode(dt, na);
        uint32_t next_index = (index + 1);
        
        float deltaTime = (float)(na->mScalingKeys[next_index].mTime - na->mScalingKeys[index].mTime);
        float factor = (dt - (float)na->mScalingKeys[index].mTime) / deltaTime;
        if (factor < 0.0f)
            factor = 0.0f;
        
        const auto& start = na->mScalingKeys[index].mValue;
        const auto& end = na->mScalingKeys[next_index].mValue;
        auto delta = end - start;
        auto aiVec = start + factor * delta;

        scale.x = aiVec.x;
        scale.y = aiVec.y;
        scale.z = aiVec.z;

        return scale;
    }

    void AnimModel::readNodeHierarchy(float anim_time, const aiNode *pNode, const glm::mat4 &parentTransform)
    {
        std::string current_node_name(pNode->mName.data);       
        glm::mat4 transform_node(fromAiToGlm(pNode->mTransformation));

        const aiNodeAnim* findedNode = findAnimNodeByName(activeAnimation, current_node_name);

        if (findedNode)
        {
            glm::vec3 translationVec = getTranslationBetweenFrames(anim_time, findedNode);
            glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(translationVec.x, translationVec.y, translationVec.z));

            glm::quat quaternion = getRotationBetweenFrames(anim_time, findedNode);
            glm::mat4 rotationMatrix = glm::toMat4(quaternion);

            glm::vec3 scaleVec = getScaleBetweenFrames(anim_time, findedNode);
            glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scaleVec.x, scaleVec.y, scaleVec.z));
            
            transform_node = translationMatrix * rotationMatrix * scaleMatrix;
        }

        glm::mat4 globalTransformMatrix = parentTransform * transform_node;

        if (bones_map.find(current_node_name) != bones_map.end())
        {
            uint32_t BoneIndex = bones_map[current_node_name];
            bones_info[BoneIndex].transform = global_inverse_transform * globalTransformMatrix * bones_info[BoneIndex].offset;
        }

        for (uint32_t i = 0; i < pNode->mNumChildren; i++)
        {
            readNodeHierarchy(anim_time, pNode->mChildren[i], globalTransformMatrix);
        }
    }

    void AnimModel::transformBones(float dt)
    {
        readNodeHierarchy(dt, scene->mRootNode, glm::mat4(1.0f));
        bone_transformation.resize(bones_count);
        for (uint32_t i = 0; i < bones_count; i++)
        {
            bone_transformation[i] = bones_info[i].transform;
        }
    }

    void AnimModel::updateNodeTransform(aiNode *node, const glm::mat4 &parent_transform)
    {
        glm::mat4 transform = parent_transform * fromAiToGlm(node->mTransformation);
        for (uint32_t i = 0; i < node->mNumMeshes; i++)
        {
            uint32_t mesh = node->mMeshes[i];
            anim_meshes[mesh].transform = transform;
        }   

        for (uint32_t i = 0; i < node->mNumChildren; i++)
            updateNodeTransform(node->mChildren[i], transform);
    }
}