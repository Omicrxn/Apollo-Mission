#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"

#include "Point.h"
#include "SString.h"

#include "SDL/include/SDL.h"
class Body;
enum class PlayerAnim
{
    IDLE,
    WALK,
    JUMP,
    CLIMB
};

class Player: public Entity
{
public:

    Player();

    bool Update(float dt);

    bool Draw();

    void SetTexture(SDL_Texture *tex);

    SDL_Rect GetBounds();

private:
    void HorizontalMove(bool isLeft);
    void Propulsion(bool isUp);

    Vec2f earthMaxGravity = { 0.0f,0.0f };
    Vec2f earthGravity = { 0.0f,0.0f };
    uint earthGravityStart = 0;
    uint earthGravityEnd = 0;

    Vec2f moonMaxGravity = { 0.0f,0.0f };
    Vec2f moonGravity = { 0.0f,0.0f };
    uint moonGravityStart = 0;
    uint moonGravityEnd = 0;

public:

    SDL_Texture* texture = nullptr;   // Player spritesheet

    // TODO: Define all animation properties
    PlayerAnim currentAnim;

    int width = 0, height = 0;
    SDL_Rect rect = { 0,0,0,0 };
    Vec2f tempPosition = Vec2f(0.0f, 0.0f);

    bool readyToJump = true;
    bool hitObstacle = false;

    Body* body = nullptr;
};

#endif // __PLAYER_H__