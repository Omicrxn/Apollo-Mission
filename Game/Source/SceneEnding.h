#pragma once
#ifndef __SCENE_ENDING_H__
#define __SCENE_ENDING_H__

#include "SDL/include/SDL.h"
#include "Scene.h"

class Font;

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

    Font* font = nullptr;
};

#endif // __SCENETITLE_H__