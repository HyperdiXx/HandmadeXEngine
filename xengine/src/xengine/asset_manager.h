#pragma once

#ifndef XE_ASSET_MANAGER
#define XE_ASSET_MANAGER

#include <xe_types.h>

#include "xe_audio.h"
#include "xe_image.h"

namespace xe_scene
{
    struct Scene;
}

namespace xe_audio
{
    struct AudioClip;
}


enum class AudioType
{
    NONE,
    MP3,
    OM
};

class AudioLoader
{
public:

    bool32 loadAudioClip(const char *path, xe_audio::AudioClip *audiClip);
    bool32 loadAudioClip(const std::string &path, xe_audio::AudioClip *audiClip);
};

class SceneLoader
{
public:

    static bool32 loadScene(const char *path, xe_scene::Scene *scn);
    static bool32 loadScene(const std::string &path, xe_scene::Scene *scn);
};

class ImageLoader
{
public:

    static bool32 loadImage(const char *path, xe_image::Image *img);
    static bool32 loadImage(const std::string &path, xe_image::Image *img);


    static bool32 loadImagePNG();
    static bool32 loadImageBMP();
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

class AssetManager
{
public:

    static const ImageLoader *getImageLoader() { return &image_loader; }
    static const AudioLoader *getAudioLoader() { return &audio_loader; }
    static const SceneLoader *getSceneLoader() { return &scene_loader; }
    static const ModelLoader *getModelLoader() { return &model_loader; }

private:

    AssetManager() = delete;

    AssetManager(const AssetManager&) = delete;
    AssetManager(AssetManager&&) = delete;

    ~AssetManager() = delete;

private:
    static ImageLoader image_loader;
    static AudioLoader audio_loader;
    static SceneLoader scene_loader;
    static ModelLoader model_loader;
};
#endif // !XE_ASSET_MANAGER

