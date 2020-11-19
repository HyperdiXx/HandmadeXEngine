#pragma once

#include <assimp/include/assimp/Importer.hpp>
#include <assimp/include/assimp/scene.h>
#include <assimp/include/assimp/postprocess.h>


class Asset
{
public:
    virtual ~Asset() {};

    virtual void serialize() = 0;
    virtual void deserialize() = 0;

    inline uint32 getResID() const { return asset_id; }

protected:
    //add hash
    uint32 asset_id;
};

class TextureAsset : public Asset
{
public:
    TextureAsset() {};

    void serialize() override;
    void deserialize() override;

public:
    void *texture_info;
    int32 width, height;
    int32 channels;
};

class ModelAsset : public Asset
{
public:

    ModelAsset() {};

    void serialize() override;
    void deserialize() override;

    std::string parent_dir;
    std::vector<TextureWrapper> model_textures;
};

class AnimModelAsset : public Asset
{
public:

    AnimModelAsset() {};

    void serialize() override;
    void deserialize() override;

private:

};

class Scene : public Asset
{
public:
    Scene() {};
    Scene(const std::string &na) : name(na) {};

    void serialize() override;
    void deserialize() override;

    inline const std::string &getName() { return name; }

private:
    std::string name;
    DynArray<Entity> entities;
};


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

    std::vector<Triangle> triangles;

    Material *material;

    VertexArray vao;
    AABB bounding_box;
};

struct ModelNode
{
    void addChild(ModelNode* child);
    void addMesh(Mesh *msh);

    std::string name;
    std::vector<Mesh*> meshes;
    std::vector<ModelNode*> children;
};

struct Model
{
public:
    Model() = default;

    Model(Model && m);
    Model &operator=(Model && m) noexcept;

    ModelNode* root;
    Vertex *vertex_type;

    ModelAsset asset_data;

    std::vector<ModelNode*> nodes;
};

struct Bone
{
    Matrix4x4 transform;
    Matrix4x4 offset;
};

Matrix4x4 fromAiToMat4x4(const aiMatrix4x4 &ai_mat);

std::vector<TextureWrapper> loadTexturesFromMaterial(Model *mdl, aiMaterial *material, aiTextureType type, std::string texture_type);

Vertex* getVertexType(Model *mdl);

void parseMaterials(Model *m, Mesh *Mesh, aiMesh* ai_Mesh, const aiScene *scene);
void parseVert(Mesh* meh, aiMesh *aiMesh);

void parseFaces(Mesh* Mesh, aiMesh *aiMesh);
Mesh* parseMesh(Model *Model, aiMesh* ai_Mesh, const aiScene *scene);

ModelNode* parseNode(Model* Model, aiNode* ai_node, const aiScene *scene);

void memCpyvec(aiVector3D & aivec3, Vec3 &vec3);
void memCpymatrix(aiMatrix4x4 & aimat, Matrix4x4 &mat4);

void calcWeight(uint32 id, real32 weight, Vec4i& bone_id, Vec4& wts);

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
    uint32 start_vertex;
    uint32 start_index;
    uint32 index_count;
    uint32 material_index;

    Matrix4x4 transform;
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

    Matrix4x4 global_inverse_transform;

    std::vector<PositionNormalUVBW> anim_vertices;
    std::vector<uint32> anim_indices;
    std::vector<Matrix4x4> bone_transformation;

    uint32 bones_count = 0;
    real32 animation_speed = 0.75f;
    real32 animation_time = 0.0f;

    aiAnimation* activeAnimation;
    VertexArray va;

    void setActiveAnimation(uint32 anim_index)
    {
        assert(anim_index < scene->mNumAnimations);
        activeAnimation = scene->mAnimations[anim_index];
    }

    void update(real32 dt);
private:
    const aiNodeAnim *findAnimNodeByName(const aiAnimation* animation, const std::string &node_name);

    uint32 getTranslationIndexForNode(real32 anim_time, const aiNodeAnim* node_anim);
    uint32 getRotationIndexForNode(real32 anim_time, const aiNodeAnim* node_anim);
    uint32 getScaleIndexForNode(real32 anim_time, const aiNodeAnim* node_anim);

    Vec3 getTranslationBetweenFrames(real32 dt, const aiNodeAnim *na);
    Quaternion getRotationBetweenFrames(real32 dt, const aiNodeAnim *na);
    Vec3 getScaleBetweenFrames(real32 dt, const aiNodeAnim *na);
    void readNodeHierarchy(real32 anim_time, const aiNode* pNode, const Matrix4x4& parentTransform);

    void transformBones(real32 dt);
    void updateNodeTransform(aiNode *node, const Matrix4x4 &parent_transform = createMat4x4());
};
   