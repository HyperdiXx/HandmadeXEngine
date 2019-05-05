#include "assetmanager.h"


namespace XEngine
{
    namespace Assets
    {
        std::unordered_map<uint32, Rendering::BasicMaterial*> AssetManager::materials;
        std::unordered_map<uint32, Rendering::BPMaterial*> AssetManager::bpmaterials;
        std::unordered_map<uint32, Rendering::PBRMaterial*> AssetManager::pbrmaterials;
        std::unordered_map<std::string, Model*> AssetManager::models;

        uint32 AssetManager::getNumMaterials()
        {
            return materials.size();
        }



    }
}