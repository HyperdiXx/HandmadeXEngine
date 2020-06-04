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

    glm::mat4 from_ai_to_glm(const aiMatrix4x4 &ai_mat);
 
    std::vector<texture_wrapper> load_textures_from_material(model *mdl, aiMaterial *material, aiTextureType type, std::string texture_type);    
    
    vertex* get_vertex_type(model *mdl);

    void parse_materials(model *m, mesh *mesh, aiMesh* ai_mesh, const aiScene *scene);
    void parse_vert(mesh* meh, aiMesh *aimesh);
    void parse_faces(mesh* mesh, aiMesh *aimesh);
    mesh* parse_mesh(model *model, aiMesh* ai_mesh, const aiScene *scene);
    
    node* parse_node(model* model, aiNode* ai_node, const aiScene *scene);

    void mem_cpyvec(aiVector3D & aivec3, glm::vec3 &vec3);
    void mem_cpymatrix(aiMatrix4x4 & aimat, glm::mat4 &mat4);

    void calc_weight(uint32 id, real32 weight, glm::ivec4& bone_id, glm::vec4& wts);

    model *parse_static_model(const aiScene* scene, const std::string &path);
    model* load_model_from_file(const std::string &path, bool32 calculate_tb = true);

    class AnimatedNode
    {
    public:
        uint32_t start_vertex;
        uint32_t start_index;
        uint32_t index_count;
        uint32_t material_index;
        
        glm::mat4 transform;
    };

    class AnimatedModel
    {
    public:
        AnimatedModel() {};
        AnimatedModel(const std::string &path);

        std::unique_ptr<Assimp::Importer> assimp_importer;
        const aiScene* scene;

        std::vector<AnimatedNode> anim_meshes;
        std::unordered_map<std::string, uint32_t> bones_map;
        std::vector<bone> bones_info;
        
        glm::mat4 global_inverse_transform;
        
        std::vector<pos_normal_uv_b_w> anim_vertices;
        std::vector<uint32_t> anim_indices;
        std::vector<glm::mat4> bone_transformation;


        int32_t bones_count = 0;
        float animation_speed = 0.75f;
        float animation_time = 0.0f;

        aiAnimation* activeAnimation;
        vertex_array va;

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


    class Animation
    {
        std::string name;
        float duration = 0.0f;
        float animation_speed = 0.75f;
        float animation_time = 0.0f;
        float ticks_per_second = 0.0f;

        bool is_playing = true;
    };
}
