#pragma once

#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H

#include <xenpch.h>
#include <runtime/core/utility/log.h>

namespace XEngine
{
    namespace Assets
    {
        class Model;
        class AnimatedModel;
    }
     
    class ModelLoader
    {
    public:
        static Assets::Model* load_model_from_file(const std::string const & path);
        static Assets::AnimatedModel* load_anim_model_from_file(const std::string const & path);
    };  
}
#endif // !MODEL_LOADER_H

