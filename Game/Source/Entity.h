#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Point.h"
#include "CustomMath.h"
#include "SString.h"

enum class EntityType
{
    PLAYER,
    ASTEROID,
    UNKNOWN
};

class Entity
{
public:

    Entity(EntityType type) : type(type), active(true) {}

    virtual bool Update(float dt)
    {
        return true;
    }
    virtual bool CleanUp()
    {
        return true;
    }


public:

    EntityType type = EntityType::UNKNOWN;
    bool active = true;
    //SString name;         // Entity name identifier?
    //uint32 id;            // Entity identifier?

    // Possible properties, it depends on how generic we
    // want our Entity class, maybe it's not renderable...
    bool renderable = false;
    //SDL_Texture* texture;
};

#endif // __ENTITY_H__