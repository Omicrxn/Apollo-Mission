#include "SceneEnding.h"

#include "App.h"
#include "Render.h"


#include "Textures.h"

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

    return false;
}

bool SceneEnding::Update(float dt)
{
    

    return false;
}

bool SceneEnding::Draw()
{
    app->render->DrawTexture(bgText, 0, 0, &bgRect);
    return false;
}

bool SceneEnding::Unload()
{


    return false;
}
