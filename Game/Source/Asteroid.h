#ifndef __ASTEROID_H__
#define __ASTEROID_H__

#include "Entity.h"

#include "Point.h"
#include "SString.h"
#include "CustomMath.h"

#include "SDL/include/SDL.h"

class CircleCollision;

class Asteroid : public Entity
{
public:

    Asteroid();

    bool Update(float dt);

    bool Draw();

    void SetTexture(SDL_Texture* tex);

    void SetPosition(Vec2i position);

public:

    SDL_Texture* texture = nullptr; // Asteroid sprite

    int width = 0, height = 0;
    SDL_Rect rect = { 0,0,0,0 };

    CircleCollision* collider = nullptr;

    Vec2i position = { 0,0 };
};

#endif // __ASTEROID_H__
