#pragma once

#ifndef ANIMATED_MODEL_H
#define ANIMATED_MODEL_H

#include <runtime/geometry/model.h>

namespace XEngine
{
    namespace Assets
    {
        struct Bone
        {
            uint32 id;
            std::string name;
            Bone* parent;
            glm::mat4 offset;
        };

        struct BoneNode : Node
        {
            glm::mat4 transform;
        };

        class AnimatedModel : public Model
        {
        public:

            void add_animation();
            void set_animation();
            void map_node(Node *node);
            void add_bone(Bone *bone);

            BoneNode* root;
        private:

        };
    }
}


#endif // !ANIMATED_MODEL_H

