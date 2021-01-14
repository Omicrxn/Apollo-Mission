#ifndef __SCENEGAMEPLAY_H__
#define __SCENEGAMEPLAY_H__

#include "Scene.h"

#include "Player.h"

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



private:

    Player* player = nullptr;
    SDL_Rect camera = { 0,0,0,0 };

    SDL_Texture* space = nullptr;
    SDL_Rect spaceRect = { 0,0,1280,720 };
};

#endif // __SCENEGAMEPLAY_H__