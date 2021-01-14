#include "SceneTitle.h"

#include "App.h"
#include "Render.h"
#include "Input.h"
#include "Font.h"

#include "EntityManager.h"

#include "SDL/include/SDL.h"


SceneTitle::SceneTitle()
{
    // GUI: Initialize required controls for the screen
    btnStart = new GuiButton(1, { 1280/2 - 300/2, 300, 300, 80 }, "START");
    btnStart->SetObserver(this);

    btnExit = new GuiButton(2, { 1280/2 - 300/2, 400, 300, 80 }, "EXIT");
    btnExit->SetObserver(this);
}

SceneTitle::~SceneTitle()
{
}

bool SceneTitle::Load()
{
    font = new Font("Assets/Fonts/londrina.xml");

    return false;
}

bool SceneTitle::Update(float dt)
{
    if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) TransitionToScene(SceneType::GAMEPLAY);

    btnStart->Update(dt);
    btnExit->Update(dt);

    return false;
}

bool SceneTitle::Draw()
{
    app->render->DrawRectangle({ 0, 0, 1280, 720 }, { 100, 100, 80, 255 });

    btnStart->Draw();
    btnExit->Draw();

    char score[64] = { 0 };
    sprintf_s(score, 64, "SCORE: %03i", 56);

    app->render->DrawText(font, score, 10, 10, 200, 0, { 255, 0, 255, 255 });

    return false;
}

bool SceneTitle::Unload()
{
    return false;
}

//----------------------------------------------------------
// Manage GUI events for this screen
//----------------------------------------------------------
bool SceneTitle::OnGuiMouseClickEvent(GuiControl* control)
{
    switch (control->type)
    {
    case GuiControlType::BUTTON:
    {
        if (control->id == 1) TransitionToScene(SceneType::GAMEPLAY);
        else if (control->id == 2) return false; // TODO: Exit request
    }
    default: break;
    }

    return true;
}