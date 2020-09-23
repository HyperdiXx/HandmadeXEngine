#ifndef ECS_H
#define ECS_H

global uint32 idEntity = 1;

struct Entity
{
    Entity() : id(idEntity++) {};    

    uint32 id;
};


#endif // !ECS_H
