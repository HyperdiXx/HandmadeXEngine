#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "xe_graphics_resource.h"
#include "xe_render.h"

#include "xe_math.h"
#include <unordered_map>

#include <types.h>
#include <glm/glm.hpp>

namespace xe_assets
{
    using namespace xe_graphics;

    struct Mesh
    {
        void addVertex(PositionNormalUV vertex);
        void addVertex(PositionNormalTBUV vertex);
        void addVertex(real32 vertex);

        void addIndex(uint32 ind);        

        std::vector<real32> vertices_fl;

        std::vector<PositionNormalUV> vertices;
        std::vector<PositionNormalTBUV> vertices_tab;

        std::vector<uint32> indices;
        std::vector<TextureWrapper> mesh_textures;

        xe_graphics::VertexArray vao;
        aabb bounding_box;
    };

    struct Node
    {
        void addChild(Node* child);
        void addMesh(Mesh *msh);

        std::string name;
        std::vector<Mesh*> meshes;
        std::vector<Node*> children;
    };

    struct Model
    {
    public:
        Model() = default;
        
        Model(Model && m);
        Model &operator=(Model && m) noexcept;

        Node* root;
        Vertex *vertex_type;
        std::string parent_dir;
        std::vector<TextureWrapper> model_textures;
        std::vector<Node*> nodes;
    };

    struct Bone
    {
        glm::mat4 transform;
        glm::mat4 offset;        
    };

    glm::mat4 fromAiToGlm(const aiMatrix4x4 &ai_mat);
 
    std::vector<TextureWrapper> loadTexturesFromMaterial(Model *mdl, aiMaterial *material, aiTextureType type, std::string texture_type);    
    
    Vertex* getVertexType(Model *mdl);

    void parseMaterials(Model *m, Mesh *Mesh, aiMesh* ai_Mesh, const aiScene *scene);
    void parseVert(Mesh* meh, aiMesh *aiMesh);

    void parseFaces(Mesh* Mesh, aiMesh *aiMesh);
    Mesh* parseMesh(Model *Model, aiMesh* ai_Mesh, const aiScene *scene);
    
    Node* parseNode(Model* Model, aiNode* ai_node, const aiScene *scene);

    void memCpyvec(aiVector3D & aivec3, glm::vec3 &vec3);
    void memCpymatrix(aiMatrix4x4 & aimat, glm::mat4 &mat4);

    void calcWeight(uint32 id, real32 weight, glm::ivec4& bone_id, glm::vec4& wts);

    Model* parseStaticModel(const aiScene* scene, const std::string &path);
    Model* loadModelFromFile(const std::string &path, bool32 calculate_tb = true);

    struct Animation
    {
        std::string name;
        float duration = 0.0f;
        float animation_speed = 0.75f;
        float animation_time = 0.0f;
        float ticks_per_second = 0.0f;

        bool is_playing = true;
    };

    struct AnimNode
    {
    public:
        uint32_t start_vertex;
        uint32_t start_index;
        uint32_t index_count;
        uint32_t material_index;
        
        glm::mat4 transform;
    };

    class AnimModel
    {
    public:
        AnimModel() = default;
        AnimModel(const std::string &path);
        
        AnimModel(const AnimModel &m) = default;
        AnimModel(AnimModel && m);

        AnimModel &operator=(AnimModel && m) noexcept;

        std::unique_ptr<Assimp::Importer> assimp_importer;
        const aiScene* scene;

        std::vector<AnimNode> anim_meshes;
        std::unordered_map<std::string, uint32_t> bones_map;
        std::vector<Bone> bones_info;
        
        glm::mat4 global_inverse_transform;
        
        std::vector<PositionNormalUVBW> anim_vertices;
        std::vector<uint32_t> anim_indices;
        std::vector<glm::mat4> bone_transformation;


        int32_t bones_count = 0;
        float animation_speed = 0.75f;
        float animation_time = 0.0f;

        aiAnimation* activeAnimation;
        VertexArray va;

        void set_active_animation(uint32_t anim_index)
        {
            assert(anim_index < scene->mNumAnimations);
            activeAnimation = scene->mAnimations[anim_index];
        }

        void update(float dt);       
    private:
        const aiNodeAnim *findAnimNodeByName(const aiAnimation* animation, const std::string &node_name);

        uint32_t getTranslationIndexForNode(float anim_time, const aiNodeAnim* node_anim);
        uint32_t getRotationIndexForNode(float anim_time, const aiNodeAnim* node_anim);
        uint32_t getScaleIndexForNode(float anim_time, const aiNodeAnim* node_anim);

        glm::vec3 getTranslationBetweenFrames(float dt, const aiNodeAnim *na);
        glm::quat getRotationBetweenFrames(float dt, const aiNodeAnim *na);
        glm::vec3 getScaleBetweenFrames(float dt, const aiNodeAnim *na);
        void readNodeHierarchy(float anim_time, const aiNode* pNode, const glm::mat4& parentTransform);

        void transformBones(float dt);
        void updateNodeTransform(aiNode *node, const glm::mat4 &parent_transform = glm::mat4(1.0f));
    };
}
