#pragma once
#ifndef __SCENE_ENDING_H__
#define __SCENE_ENDING_H__
#include "SDL/include/SDL.h"
#include "Scene.h"
class SceneEnding : public Scene
{
public:

    SceneEnding();
    virtual ~SceneEnding();

    bool Load();

    bool Update(float dt);

    bool Draw();

    bool Unload();

private:
    SDL_Texture* bgText = nullptr;
    SDL_Rect bgRect = { 0,0,1280,720 };
};

#endif // __SCENETITLE_H__