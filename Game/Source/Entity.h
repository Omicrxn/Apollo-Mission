#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Point.h"
#include "Vec2.h"
#include "SString.h"

#include "Collisions.h"

enum class EntityType
{
    PLAYER,
    ENEMY,
    ITEM,
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

    const Collider* GetCollider() const { return collider; }

    virtual void OnCollision(Collider* collider) {};

public:

    EntityType type = EntityType::UNKNOWN;
    bool active = true;
    //SString name;         // Entity name identifier?
    //uint32 id;            // Entity identifier?

    // Possible properties, it depends on how generic we
    // want our Entity class, maybe it's not renderable...
    bool renderable = false;
    //SDL_Texture* texture;

    Collider* collider = nullptr;
};

#endif // __ENTITY_H__