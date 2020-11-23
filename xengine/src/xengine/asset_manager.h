#pragma once

#ifndef XE_ASSET_MANAGER
#define XE_ASSET_MANAGER

internal
std::string concatPath(const char *path, const char *dir);

class AudioLoader
{
public:

    enum class AudioType
    {
        NONE,
        MP3,
        OM
    };

    bool32 loadAudioClip(const char *path, AudioClip *audiClip);
    bool32 loadAudioClip(const std::string &path, AudioClip *audiClip);
};

class SceneLoader
{
public:

    static bool32 loadScene(const char *path, Scene *scn);
    static bool32 loadScene(const std::string &path, Scene *scn);
};

class TextureLoader
{
public:

    static void* loadTexture2D(const char *path);
    static bool32 loadTexture2D(const std::string &path);


    static bool32 loadTexturePNG();
    static bool32 loadTextureBMP();
};

class ModelLoader
{
public:

    static bool32 loadModel(const char *path);
    static bool32 loadAnimModel(const char *path);

private:
    enum class ModelType
    {
        Static,
        Animated
    };

    ModelType type;
};

class AbstractAssetFactory
{
public:
    global Asset* loadAsset(const char *resolved_path, AssetType type);

    global StaticModelAsset* loadStaticModel(const char *path);
    global AnimModelAsset* loadAnimModel(const char *path);
    global AudioClip* loadAudioClip(const char *path);
    global TextureAsset *loadTexture(const char *name);
    global Scene *loadScene(const char *name);
    
    global const TextureLoader *getTextureLoader() 
    { 
        static TextureLoader tex_loader;
        return &tex_loader; 
    }
    
    global const AudioLoader *getAudioLoader()
    {
        static AudioLoader audio_loader;
        return &audio_loader; 
    }
    
    global const SceneLoader *getSceneLoader() 
    {
        static SceneLoader scene_loader;
        return &scene_loader; 
    }
    
    global const ModelLoader *getModelLoader() 
    {
        static ModelLoader model_loader;
        return &model_loader; 
    }

private:

    AbstractAssetFactory() = delete;

    AbstractAssetFactory(const AbstractAssetFactory&) = delete;
    AbstractAssetFactory(AbstractAssetFactory&&) = delete;

    ~AbstractAssetFactory() = delete;
private: 
};

class AssetManager
{
public:

    TextureAsset* getTextureAsset(const char *path);
    StaticModelAsset* getStaticModelAsset(const char *path);
    AnimModelAsset* getAnimModelAsset(const char *path);

    void setResourcePath(const std::string &p) { resource_path = p; }

public:
    global AssetManager *getInstance()
    {
        global AssetManager mng = {};
        return &mng;
    }

private:
    std::unordered_map<std::string, StaticModelAsset*> static_models;
    std::unordered_map<std::string, AnimModelAsset*> anim_models;
    std::unordered_map<std::string, TextureAsset*> textures;

    std::string resource_path;
};

class ResourceManager
{
public:
    
    Model *getModel(const char *path, bool32 calculate_tb = true);
    AnimModel *getAnimModel(const char *path, bool32 calculate_tb = true);
    
public:
    
    global ResourceManager *getInstance()
    {
        global ResourceManager mng = {};
        return &mng;
    }

private:

    ModelNode* parseNode(Model *model, aiNode *ai_node);
    Model* parseStaticModel(const std::string &path);
    Model* loadStaticModelFromFile(const std::string &path, bool32 calculate_tb = true);

    AnimModel *loadAnimModelFromFile(const std::string &path, bool32 calculate_tb = true);

private:
    std::unordered_map<std::string, Model*> static_models;
    std::unordered_map<std::string, AnimModel*> anim_models;
    
    // EnvironmentMaps
    // Skyboxes

    Assimp::Importer m_importer = {};
    const aiScene* m_scene;
};

#endif // !XE_ASSET_MANAGER

