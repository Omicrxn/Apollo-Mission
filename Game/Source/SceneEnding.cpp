#include "SceneEnding.h"

#include "App.h"
#include "Render.h"
#include "Window.h"

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
    app->render->camera = { 0,0 };

    font = new Font("Assets/Fonts/future_font.xml");

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
    int offset = 3;
    app->render->DrawRectangle(SDL_Rect{ 0, 0, 1280, 720 }, SDL_Color{ 0,0,0,255 }, true);
    app->render->DrawText(font, "GAME OVER", (int)app->win->GetWindowWidth() / 4 + 80 + offset, (int)app->win->GetWindowHeight() / 2 - 100 + offset, 75, 13, { 105,105,105,255 });
    app->render->DrawText(font, "GAME OVER", (int)app->win->GetWindowWidth() / 4 + 80, (int)app->win->GetWindowHeight() / 2 - 100, 75, 13, { 255,0,0,255 });

    app->render->DrawText(font, "VICTORY", (int)app->win->GetWindowWidth() / 4 + 150 + offset, (int)app->win->GetWindowHeight() / 2 - 100 + offset, 75, 13, { 105,105,105,255 });
    app->render->DrawText(font, "VICTORY", (int)app->win->GetWindowWidth() / 4 + 150, (int)app->win->GetWindowHeight() / 2 - 100, 75, 13, { 0,255,0,255 });

    app->render->DrawText(font, "Press 'ENTER' to continue", (int)app->win->GetWindowWidth() / 2 - 290 + offset, (int)app->win->GetWindowHeight() / 2 + 23 + offset, 40, 5, { 105,105,105,255 });
    app->render->DrawText(font, "Press 'ENTER' to continue", (int)app->win->GetWindowWidth() / 2 - 290, (int)app->win->GetWindowHeight() / 2 + 23, 40, 5, { 255,255,255,255 });
    return false;
}

bool SceneEnding::Unload()
{
    delete font;
    return false;
}
