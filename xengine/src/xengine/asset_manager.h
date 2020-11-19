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

    enum class AssetType
    {
        Texture1D,
        Texture2D,
        Texture3D,
        Model,
        AnimModel,
        Audio,
        Scene
    };

    global Asset* loadAsset(const char *name, const char *dir, AbstractAssetFactory::AssetType type);

    global Model loadModel(const char *name, const char *dir);
    global AnimModel loadAnimModel(const char *name, const char *dir);
    global AudioClip loadAudioClip(const char *name, const char *dir);
    global TextureAsset *loadTexture2D(const char *name, const char *dir);
    global Scene *loadScene(const char *name, const char *dir);
    
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

    global AssetManager *getInstance()
    {
        global AssetManager mng = {};
        return &mng;
    }

private:
    std::vector<Model> models;
    std::vector<AnimModel> anim_models;
};


#endif // !XE_ASSET_MANAGER

