
#ifndef ASSET_MANAGER_CPP
#define ASSET_MANAGER_CPP

std::string concatPath(const char *path, const char *dir)
{
    std::string result(path);

    if (dir)
    {
        std::string dirname(dir);
        result = dirname + '/' + result;
    }

    return result;
}

Model AbstractAssetFactory::loadModel(const char *name, const char *dir)
{
    Model result = {};

    return result;
}

AnimModel AbstractAssetFactory::loadAnimModel(const char *name, const char *dir)
{
    AnimModel result = {};

    return result;
}

AudioClip AbstractAssetFactory::loadAudioClip(const char *name, const char *dir)
{
    AudioClip result = {};

    return result;
}

TextureAsset* AbstractAssetFactory::loadTexture2D(const char *name, const char *dir)
{
    TextureAsset *result = (TextureAsset*)allocateMemory(&asset_arena, sizeof(TextureAsset));
    
    std::string path_str = concatPath(name, dir);
    const char *path_res = path_str.c_str();

    result->texture_info = xe_core::loadTextureFromDisc(path_res, result->width, result->height, result->channels, 0, true);
       
    return result;
}

Scene* AbstractAssetFactory::loadScene(const char *name, const char *dir)
{
    Scene *result = (Scene*)allocateMemory(&asset_arena, sizeof(Scene));

    

    return result;
}

Asset* AbstractAssetFactory::loadAsset(const char *name, const char *dir, AssetType type)
{
    Asset *result = 0;

    switch (type)
    {
        case AssetType::Texture1D:
        {
             
        } break;
        case AssetType::Texture2D:
        {
            TextureAsset *res = loadTexture2D(name, dir);
            result = alloc_mem(res) TextureAsset();
        } break;
        case AssetType::Texture3D:
        {

        } break;
        case AssetType::Model:
        {

        } break;
        case AssetType::AnimModel:
        {
        
        } break;
        case AssetType::Audio:
        {

        } break;
        case AssetType::Scene:
        {
            Scene *scen = loadScene(name, dir);
            result = alloc_mem(scen) Scene();
        } break;
        default:
        {

        } break;
    }

    return result;
}

#endif
