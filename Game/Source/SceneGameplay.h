#ifndef __SCENEGAMEPLAY_H__
#define __SCENEGAMEPLAY_H__

#include "Scene.h"

#include "Player.h"
#include "World.h"

class Collider;

class SceneGameplay : public Scene
{
public:

    SceneGameplay();
    virtual ~SceneGameplay();

    bool Load();

    bool Update(float dt);

    bool Draw();

    bool Unload();

    void CheckAllColisions();

private:

    Player* player = nullptr;
    SDL_Rect camera = { 0,0,0,0 };

    World* world = nullptr;

    SDL_Texture* space = nullptr;
    SDL_Rect spaceRect = { 0,0,0,0 };
    SDL_Texture* smallFighter = nullptr;
    SDL_Texture* fire = nullptr;
    SDL_Texture* explosion = nullptr;

    RectCollision* earthBottomCollision = nullptr;
    RectCollision* earthWaterCollision = nullptr;
    RectCollision* earthGroundCollision = nullptr;
    RectCollision* moonGroundCollision = nullptr;

    float fluidDensity = 0;
    float volumeSubmerged = 0;
    uint buoyancyStart = 0;
    uint buoyancyEnd = 0;
};

#endif // __SCENEGAMEPLAY_H__