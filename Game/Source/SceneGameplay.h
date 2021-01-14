#ifndef __SCENEGAMEPLAY_H__
#define __SCENEGAMEPLAY_H__

#include "Scene.h"

#include "Map.h"
#include "Player.h"

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

    Map* map = nullptr;
    Player* player = nullptr;

    SDL_Rect camera = { 0,0,0,0 };
};

#endif // __SCENEGAMEPLAY_H__