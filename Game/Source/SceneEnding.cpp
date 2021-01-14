#include "SceneEnding.h"

#include "App.h"
#include "Render.h"

#include "SDL/include/SDL.h"

SceneEnding::SceneEnding()
{
}

SceneEnding::~SceneEnding()
{
}

bool SceneEnding::Load()
{
    return false;
}

bool SceneEnding::Update(float dt)
{
    return false;
}

bool SceneEnding::Draw()
{
    SDL_Rect rec = { 0, 0, 1280, 720 };
    SDL_Color color = { 0, 0, 255, 255 };
    
    app->render->DrawRectangle(rec, color);

    return false;
}

bool SceneEnding::Unload()
{
    return false;
}