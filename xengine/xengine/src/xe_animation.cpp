#include "xe_animation.h"

#include "xe_graphics_device.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>

namespace xe_animation
{
    glm::mat4 fromAiToGlm(const aiMatrix4x4 &ai_mat)
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


    Skeleton::Skeleton()
    {

    }

    Skeleton::~Skeleton()
    {

    }

    AnimModel::AnimModel(const std::string& path)
    {
        static const uint32_t import_flags =
            aiProcess_CalcTangentSpace |        // Create binormals/tangents just in case
            aiProcess_Triangulate |             // Make sure we're triangles
            aiProcess_SortByPType |             // Split meshes by primitive type
            aiProcess_GenNormals |              // Make sure we have legit normals
            aiProcess_GenUVCoords |             // Convert UVs if required 
            aiProcess_OptimizeMeshes |          // Batch draws where possible
            aiProcess_ValidateDataStructure;    // Validation

        std::unique_ptr<Assimp::Importer> assimp_importer = std::make_unique<Assimp::Importer>();

        const aiScene* scene = assimp_importer->ReadFile(path.c_str(), import_flags);
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
                xe_graphics::PositionNormalUVBW vertex;
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
                {
                    anim_indices.push_back(face.mIndices[j]);
                }
            }

            updateNodeTransform(scene->mRootNode);

            std::unordered_map<std::string, uint32> bones_map = skelet.getBonesMap();
            std::vector<Bone> bones = skelet.getBones();

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
                        boneIndex = skelet.bones_count;
                        skelet.bones_count++;
                        Bone bi;
                        bones.push_back(bi);
                        bones[boneIndex].offset = fromAiToGlm(bone_loader->mOffsetMatrix);
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
    }

    void AnimModel::setActiveAnimation(uint32 anim_index)
    {
        if (anim_index >= 0 && anim_index < animation_list.size())
        {
            active_animation = animation_list[anim_index];
        }
    }

    const AnimNode *AnimModel::findAnimNodeByName(const Animation *animation, const std::string& node_name)
    {
        for (uint32 i = 0; i < animation->getAnimTracksCount(); i++)
        {
            const AnimNode* anim_node = animation->anim_tracks[i];
            if (std::string(anim_node->node_name.data) == node_name)
            {
                return anim_node;
            }
        }

        return nullptr;
    }

    uint32 AnimModel::getIndexForNode(AnimKeyType type, real32 anim_time, const AnimNode * node_anim)
    {
        uint32 index = 0;

        switch (type)
        {
        case xe_animation::Position:
        {   
            for (uint32 i = 0; i < node_anim->positionKeys.size(); i++)
            {
                if (anim_time < (float)node_anim->positionKeys[i + 1].time)
                {
                    index = i;
                }
            }
            break;
        }   
        case xe_animation::Rotation:
        {
            for (uint32 i = 0; i < node_anim->rotationKeys.size(); i++)
            {
                if (anim_time < (float)node_anim->rotationKeys[i + 1].time)
                {
                    index = i;
                }                   
            }
            break;

        }
        case xe_animation::Scale:
        {
            for (uint32 i = 0; i < node_anim->scaleKeys.size(); i++)
            {
                if (anim_time < (float)node_anim->scaleKeys[i + 1].time)
                {
                    index = i;                    
                }
            }
            break;
        }
        default:
            break;
        }

        return index;
    }

    glm::vec3 AnimModel::getTranslationBetweenFrames(float dt, const AnimNode *na)
    {
        glm::vec3 translation = glm::vec3();

        if (na->positionKeys.size() == 1)
        {
            auto res = na->positionKeys[0].value;
            translation.x = res.x;
            translation.y = res.y;
            translation.z = res.z;

            return translation;
        }

        uint32 index_frame = getIndexForNode(AnimKeyType::Position, dt, na);

        uint32 next_pos_index_frame = index_frame + 1;

        float deltaTime = (float)(na->positionKeys[next_pos_index_frame].time - na->positionKeys[index_frame].time);
        float Factor = (dt - (float)na->positionKeys[index_frame].time) / deltaTime;
        if (Factor < 0.0f)
            Factor = 0.0f;

        AnimVectorKey currentFrame = na->positionKeys[index_frame];
        AnimVectorKey nextFrame = na->positionKeys[next_pos_index_frame];

        const glm::vec3& start = currentFrame.value;
        const glm::vec3& end = nextFrame.value;
        glm::vec3 delta = end - start;

        auto aiVec = (start + Factor * delta);

        translation.x = aiVec.x;
        translation.y = aiVec.y;
        translation.z = aiVec.z;

        return translation;
    }

    glm::quat AnimModel::getRotationBetweenFrames(float dt, const AnimNode *na)
    {
        if (na->rotationKeys.size() == 1)
        {
            auto v = na->rotationKeys[0].value;
            return glm::quat(v.w, v.x, v.y, v.z);
        }

        uint32_t rotation_index = getIndexForNode(AnimKeyType::Rotation, dt, na);
        uint32_t rotation_index_next = (rotation_index + 1);

        real32 delta_time = (float)(na->rotationKeys[rotation_index_next].time - na->rotationKeys[rotation_index].time);
        real32 factor = (dt - (float)na->rotationKeys[rotation_index].time) / delta_time;
        if (factor < 0.0f)
            factor = 0.0f;

        const glm::quat& start_rotaion = na->rotationKeys[rotation_index].value;
        const glm::quat& end_rotation = na->rotationKeys[rotation_index_next].value;
        
        glm::quat q = glm::slerp(start_rotaion, end_rotation, factor);
        glm::normalize(q);

        return q;
    }

    glm::vec3 AnimModel::getScaleBetweenFrames(float dt, const AnimNode *na)
    {
        glm::vec3 scale = {};

        if (na->scaleKeys.size() == 1)
        {
            auto scl = na->scaleKeys[0].value;
            scale.x = scl.x;
            scale.y = scl.y;
            scale.z = scl.z;

            return scale;
        }

        uint32_t index = getIndexForNode(AnimKeyType::Scale, dt, na);
        uint32_t next_index = (index + 1);

        float deltaTime = (float)(na->scaleKeys[next_index].time - na->scaleKeys[index].time);
        float factor = (dt - (float)na->scaleKeys[index].time) / deltaTime;
        if (factor < 0.0f)
            factor = 0.0f;

        const auto& start = na->scaleKeys[index].value;
        const auto& end = na->scaleKeys[next_index].value;
        auto delta = end - start;
        auto aiVec = start + factor * delta;

        scale.x = aiVec.x;
        scale.y = aiVec.y;
        scale.z = aiVec.z;

        return scale;
    }

    void AnimModel::readNodeHierarchy(float anim_time, const aiNode* ptr_node, const glm::mat4& parent_transform)
    {
        std::string current_node_name(ptr_node->mName.data);
        glm::mat4 transform_node(fromAiToGlm(ptr_node->mTransformation));

        const AnimNode* findedNode = findAnimNodeByName(active_animation, current_node_name);

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

        glm::mat4 globalTransformMatrix = parent_transform * transform_node;

        std::unordered_map<std::string, uint32> bone_map = skelet.getBonesMap();
        std::vector<Bone> bones = skelet.getBones();

        if (bone_map.find(current_node_name) != bone_map.end())
        {
            uint32_t BoneIndex = bone_map[current_node_name];
            bones[BoneIndex].transform = global_inverse_transform * globalTransformMatrix * bones[BoneIndex].offset;
        }

        for (uint32_t i = 0; i < ptr_node->mNumChildren; i++)
        {
            readNodeHierarchy(anim_time, ptr_node->mChildren[i], globalTransformMatrix);
        }
    }

    void AnimModel::transformBones(float dt)
    {
        //readNodeHierarchy(dt, scene->mRootNode, glm::mat4(1.0f));

        std::vector<glm::mat4>& bones_transform = skelet.getBonesTransform();
        std::vector<Bone>& bones = skelet.getBones();

        bones_transform.resize(skelet.bones_count);
        for (uint32_t i = 0; i < skelet.bones_count; i++)
        {
            bones_transform[i] = bones[i].transform;
        }
    }

    void AnimModel::updateNodeTransform(aiNode *node, const glm::mat4 &parent_transform = glm::mat4(1.0f))
    {
        glm::mat4 transform = parent_transform * fromAiToGlm(node->mTransformation);
        for (uint32_t i = 0; i < node->mNumMeshes; i++)
        {
            uint32_t mesh = node->mMeshes[i];
            anim_meshes[mesh].transform = transform;
        }

        for (uint32_t i = 0; i < node->mNumChildren; i++)
        {
            updateNodeTransform(node->mChildren[i], transform);
        }
    }
}