#pragma once

#ifndef SKELETAL_ANIMATION_H
#define SKELETAL_ANIMATION_H

#include "xenpch.h"
#include "xe_types.h"

#include <assimp/include/assimp/Importer.hpp>
#include <assimp/include/assimp/scene.h>
#include <assimp/include/assimp/postprocess.h>

#include <glm/glm.hpp>

namespace xe_graphics
{
    struct PositionNormalUVBW;
} 

namespace xe_animation
{
    enum AnimKeyType
    {
        Position, 
        Rotation,
        Scale
    };

    struct AnimVectorKey
    {
        real64 time;
        glm::vec3 value;
    };

    struct AnimQuaternionKey
    {
        real64 time;
        glm::quat value;
    };

    struct AnimNode
    {
    public:
        std::string node_name;
        uint32_t start_vertex;
        uint32_t start_index;
        uint32_t index_count;
        uint32_t material_index;

        glm::mat4 transform;

        std::vector<AnimVectorKey> positionKeys;
        std::vector<AnimQuaternionKey> rotationKeys;
        std::vector<AnimVectorKey> scaleKeys;
    };

    struct Node
    {
        std::string name;
        glm::mat4 transform;
        Node *parent;
        Node *chidren;
    };

    struct Bone
    {
        glm::mat4 transform;
        glm::mat4 offset;
    };

    class Skeleton
    {
    public:        
        Skeleton();
        ~Skeleton();

        Bone* getBone(uint32 index) {};
        Bone* getBone(std::string& name) {};

        std::vector<Bone>& getBones() { return bones_info; }
        std::vector<glm::mat4>& getBonesTransform() { return bone_transformation; }
        std::unordered_map<std::string, uint32_t>& getBonesMap() { return bones_map; }
    public:
        int32 bones_count = 0;
    private:
        std::vector<Bone> bones_info;
        std::unordered_map<std::string, uint32_t> bones_map;
        std::vector<glm::mat4> bone_transformation;
    };

    class Animation
    {
    public:
        Animation() {}
        ~Animation() {}

        inline const uint32 getAnimTracksCount() const { return anim_tracks.size(); }

    public:
        std::vector<AnimNode*> anim_tracks;
    private:
        std::string name;
        float duration = 0.0f;
        float animation_speed = 0.75f;
        float animation_time = 0.0f;
        float ticks_per_second = 0.0f;

        bool is_playing = true;
    };

    class AnimModel
    {
    public:
        AnimModel() = default;
        AnimModel(const std::string &path);

        AnimModel(const AnimModel &m) = default;
        AnimModel(AnimModel && m);

        AnimModel &operator=(AnimModel && m) noexcept;

        //std::unique_ptr<Assimp::Importer> assimp_importer;
        //const aiScene* scene;

        glm::mat4 global_inverse_transform;
        std::vector<AnimNode> anim_meshes;
        std::vector<xe_graphics::PositionNormalUVBW> anim_vertices;
        std::vector<uint32> anim_indices;
       
        //aiAnimation* activeAnimation;
        //VertexArray va;

        void setActiveAnimation(uint32 anim_index);       

    private:
        const AnimNode *findAnimNodeByName(const Animation* animation, const std::string &node_name);

        uint32 getIndexForNode(AnimKeyType type, real32 anim_time, const AnimNode* node_anim);

        glm::vec3 getTranslationBetweenFrames(real32 dt, const AnimNode *na);
        glm::quat getRotationBetweenFrames(real32 dt, const AnimNode *na);
        glm::vec3 getScaleBetweenFrames(real32 dt, const AnimNode *na);
        
        void readNodeHierarchy(real32 anim_time, const aiNode* ptr_node, const glm::mat4& parent_transform);
        void transformBones(real32 dt);
        void updateNodeTransform(aiNode *node, const glm::mat4 &parent_transform = glm::mat4(1.0f));
    
    private:

        Animation* active_animation;
        std::vector<Animation*> animation_list;        
        Skeleton skelet;
    };
}

#endif