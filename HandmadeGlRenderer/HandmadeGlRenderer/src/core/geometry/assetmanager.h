#pragma once

#include "model.h"
#include "../rendering/pipeline/materials/basicmaterial.h"
#include "../rendering/pipeline/materials/bpmaterial.h"
#include "../rendering/pipeline/materials/pbrmaterial.h"
#include <unordered_map>

#include "../types.h"

namespace XEngine
{
    namespace Assets
    {
        class AssetManager
        {
        public:
            static uint32 getNumMaterials();
            static Rendering::BasicMaterial* getMaterial(uint32 id);
            static Rendering::BPMaterial* getBPMaterial(uint32 id);
            static Rendering::PBRMaterial* getPBRMaterial(uint32 id);
            static Model* getMesh(std::string id);
            static void addMaterial(uint32 id, Rendering::BasicMaterial* material);
            static void addModel(std::string id, Model* mesh);
        private:
            static std::unordered_map<uint32, Rendering::BasicMaterial*> materials;
            static std::unordered_map<uint32, Rendering::BPMaterial*> bpmaterials;
            static std::unordered_map<uint32, Rendering::PBRMaterial*> pbrmaterials;
            static std::unordered_map<std::string, Model*> models;
        };
    }
   
}
