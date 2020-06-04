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

    struct mesh
    {
        void add_vertex(pos_normal_uv vertex);
        void add_vertex(pos_normal_tb_uv vertex);
        void add_vertex(real32 vertex);

        void add_index(uint32 ind);        

        std::vector<real32> vertices_fl;

        std::vector<pos_normal_uv> vertices;
        std::vector<pos_normal_tb_uv> vertices_tab;

        std::vector<uint32> indices;
        std::vector<texture_wrapper> mesh_textures;

        xe_graphics::vertex_array vao;
        aabb bounding_box;
    };

    struct node
    {
        void add_child(node* child);
        void add_mesh(mesh *msh);

        std::string name;
        std::vector<mesh*> meshes;
        std::vector<node*> children;
    };

    struct model
    {
        node* root;
        vertex *vertex_type;
        std::string parent_dir;
        std::vector<texture_wrapper> model_textures;
        std::vector<node*> nodes;
    };

    struct bone
    {
        glm::mat4 transform;
        glm::mat4 offset;        
    };

    struct animation
    {
        std::string name;
        float duration = 0.0f;
        float animation_speed = 0.75f;
        float animation_time = 0.0f;
        float ticks_per_second = 0.0f;

        bool is_playing = true;
    };

    struct anim_node
    {
        std::string name;
        uint32_t BaseVertex;
        uint32_t BaseIndex;
        uint32_t MaterialIndex;
        uint32_t IndexCount;

        glm::mat4 transformation;
        aabb bounding_box;
    };

    struct anim_model
    {     
        anim_node *root;
        uint32_t bone_count = 0;

        glm::mat4 globalInverseTransform;
        std::unordered_map<std::string, uint32_t> bones_map;
        std::vector<bone> bonesInfos;

        std::vector<pos_normal_uv_b_w> anim_vertices;
        std::vector<anim_node> anim_meshes;

        std::vector<uint32_t> anim_indices;

        // Root inverse transform matrix
        std::vector<glm::mat4> bone_transformations;

        std::vector<texture_wrapper> model_textures;
        std::vector<animation> animations;
    };

    glm::mat4 from_ai_to_glm(const aiMatrix4x4 &ai_mat);
 
    std::vector<texture_wrapper> load_textures_from_material(model *mdl, aiMaterial *material, aiTextureType type, std::string texture_type);
    
    anim_node *find_node(anim_node *node, std::string &name);
  
    vertex* get_vertex_type(model *mdl);

    void parse_bones(anim_model *animmodel, anim_node *mesh, aiMesh *ai_mesh);
    void parse_animations(anim_model *model, const aiScene *ai_scene);
    void parse_materials(model *m, mesh *mesh, aiMesh* ai_mesh, const aiScene *scene);
    void parse_vert(mesh* meh, aiMesh *aimesh);
    void parse_faces(mesh* mesh, aiMesh *aimesh);
    mesh* parse_mesh(model *model, aiMesh* ai_mesh, const aiScene *scene);
    anim_node *parse_anim_mesh(anim_model *model, aiMesh *ai_mesh, const aiScene *scene);
   
    node* parse_node(model* model, aiNode* ai_node, const aiScene *scene);

    void mem_cpyvec(aiVector3D & aivec3, glm::vec3 &vec3);
    void mem_cpymatrix(aiMatrix4x4 & aimat, glm::mat4 &mat4);

    void calc_weight(uint32 id, real32 weight, glm::ivec4& bone_id, glm::vec4& wts);

    model *parse_static_model(const aiScene* scene, const std::string &path);
    anim_model *parse_anim_model(const aiScene* scene);

    model* load_model_from_file(const std::string &path, bool32 calculate_tb = true);
    anim_model* load_anim_model_from_file(const std::string &path, bool32 calculate_tb = true);


    class AnimMesh
    {
    public:
        uint32_t BaseVertex;
        uint32_t BaseIndex;
        uint32_t MaterialIndex;
        uint32_t IndexCount;

        glm::mat4 Transform;
        glm::vec3 Min, Max;
    };

    class AnimatedModel
    {
    public:
        AnimatedModel() {};
        AnimatedModel(const std::string &path);
        
        std::unique_ptr<Assimp::Importer> assimp_importer;
        const aiScene* scene;

        std::vector<AnimMesh> anim_meshes;
        uint32_t bonesCount = 0;
        std::unordered_map<std::string, uint32_t> boneMapping;
        std::vector<bone> bonesInfos;
        // Root inverese transform matrix
        
        glm::mat4 globalInverseTransform;
        
        std::vector<pos_normal_uv_b_w> vertex_info;
        std::vector<uint32_t> anim_indices;
        // Bone transformations
        std::vector<glm::mat4> boneTransforms;

        // Modifier for the animation 
        float animationSpeed = 0.75f;
        float animationTime = 0.0f;

        aiAnimation* activeAnimation;

        vertex_array va;

        void set_active_animation(uint32_t anim_index)
        {
            assert(anim_index < scene->mNumAnimations);
            activeAnimation = scene->mAnimations[anim_index];
        }

        void parse_bones(const aiMesh* pMesh, uint32_t vertexOffset, std::vector<pos_normal_uv_b_w>& Bones);       
        void update(float dt);
        

    private:
        const aiNodeAnim *find_anim_node_by_name(const aiAnimation* animation, const std::string &node_name);

        uint32_t GetTranslationIndexForNode(float anim_time, const aiNodeAnim* node_anim);
        uint32_t GetRotationIndexForNode(float anim_time, const aiNodeAnim* node_anim);
        uint32_t GetScaleIndexForNode(float anim_time, const aiNodeAnim* node_anim);

        glm::vec3 GetTranslationBetweenFrames(float dt, const aiNodeAnim *na);
        glm::quat GetRotationBetweenFrames(float dt, const aiNodeAnim *na);
        glm::vec3 GetScaleBetweenFrames(float dt, const aiNodeAnim *na);
        void readNodeHierarchy(float anim_time, const aiNode* pNode, const glm::mat4& parentTransform);

        void transform_bones(float dt);
        void updateNodeTransform(aiNode *node, const glm::mat4 &parent_transform = glm::mat4(1.0f));
    };

}
