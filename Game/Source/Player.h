#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "Animation.h"

#include "Point.h"
#include "SString.h"

#include "SDL/include/SDL.h"

class Body;
class Font;

enum class Location
{
    SPACE,
    WATER,
    GROUND,
    MOON
};

class Player: public Entity
{
public:

    Player();

    bool Update(float dt);

    bool Draw();

    void SetTextures(SDL_Texture* tex, SDL_Texture* tex2, SDL_Texture* tex3);
    
    void SetFont(Font* font);

    SDL_Rect GetBounds();

    Vec2f GetGravity();

private:
    void HorizontalMove(bool isLeft);
    void Propulsion(bool isUp, uint angle);

    SDL_Texture* texture = nullptr;   // Player spritesheet
    SDL_Rect rect = { 0,0,0,0 };

    SDL_Texture* fireTexture = nullptr;   // Fire sprite
    SDL_Rect fireRect = { 0,0,0,0 };

    SDL_Texture* explosionTexture = nullptr;

    Vec2f earthMaxGravity = { 0.0f,0.0f };
    uint earthGravityStart = 0;
    uint earthGravityEnd = 0;

    Vec2f moonMaxGravity = { 0.0f,0.0f };
    uint moonGravityStart = 0;
    uint moonGravityEnd = 0;

    Animation smallFighterTurnLeft;
    Animation smallFighterTurnRight;
    Animation explosion;
    bool animLeft = false;
    bool animRight = false;

    bool fireDraw = false;
    int fxPropulsion = 0;
    int fxDie = 0;

    Font* fontUI = nullptr;

public:

    Vec2f earthGravity = { 0.0f,0.0f };
    Vec2f moonGravity = { 0.0f,0.0f };

    Location currentLocation = Location::SPACE;

    int width = 0, height = 0;
    Body* body = nullptr;

    uint angle = 0;
    bool explode = false;
    bool propulsion = true;
};

#endif // __PLAYER_H__