#ifndef __STAGEBODY_H__
#define __STAGEBODY_H__

#include "Entity.h"

#include "Point.h"
#include "SString.h"

#include "SDL/include/SDL.h"

class Body;

class StageBody : public Entity
{
public:

    StageBody();

    bool Update(float dt);

    bool Draw();

    void SetTexture(SDL_Texture* tex);

    SDL_Rect GetBounds();

public:

    SDL_Texture* texture = nullptr;   // Player spritesheet

    int width = 0, height = 0;
    SDL_Rect rect = { 0,0,0,0 };

    //bool readyToJump = true;
    bool hitObstacle = false;

    Body* body = nullptr;
};

#endif // __STAGEBODY_H__#pragma once
