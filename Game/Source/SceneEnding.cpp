#include "SceneEnding.h"

#include "App.h"
#include "Render.h"


#include "Textures.h"
#include "Input.h"

#include "SceneManager.h"


#include "SDL/include/SDL.h"

SceneEnding::SceneEnding()
{

}

SceneEnding::~SceneEnding()
{
}

bool SceneEnding::Load()
{
    bgText = app->tex->Load("Assets/Textures/GameOver.png");
    app->render->camera = { 0,0 };
    return false;
}

bool SceneEnding::Update(float dt)
{
    
    if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {
        TransitionToScene(SceneType::TITLE);
    }
    return false;
}

bool SceneEnding::Draw()
{
    app->render->DrawTexture(bgText, 0, 0, &bgRect);
    return false;
}

bool SceneEnding::Unload()
{
    app->tex->UnLoad(bgText);

    return false;
}
