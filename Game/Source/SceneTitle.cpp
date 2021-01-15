#include "SceneTitle.h"

#include "App.h"
#include "Render.h"
#include "Input.h"
#include "Window.h"
#include "Textures.h"
#include "Font.h"
#include "SceneManager.h"
#include "Audio.h"

#include "SDL/include/SDL.h"

SceneTitle::SceneTitle()
{
    mousePos = { 0,0 };
    clicking = false;
    hoverFx = -1;
    clickFx = -1;

    mouseCursorRect[0] = { 30,482,30,30 };
    mouseCursorRect[1] = { 60,482,30,30 };

    menuCurrentSelection = MenuSelection::NONE;
}

SceneTitle::~SceneTitle()
{
}

bool SceneTitle::Load()
{
    atlasGUITexture = app->tex->Load("Assets/Textures/UI/ui_buttons_sheet.png");

    hoverFx = app->audio->LoadFx("Assets/Audio/Fx/bong.ogg");
    clickFx = app->audio->LoadFx("Assets/Audio/Fx/click.ogg");

    // GUI: Initialize required controls for the screen
    buttonStart = new GuiButton(1, { (int)app->win->GetWindowWidth() / 2 - 190 / 2, (int)app->win->GetWindowHeight() / 2 + 20, 190, 40 }, hoverFx, clickFx);
    buttonStart->SetObserver(this);

    buttonCredits = new GuiButton(2, { (int)app->win->GetWindowWidth() / 2 - 190 / 2, (int)app->win->GetWindowHeight() / 2 + 80, 190, 40 }, hoverFx, clickFx);
    buttonCredits->SetObserver(this);

    buttonExit = new GuiButton(3, { (int)app->win->GetWindowWidth() / 2 - 190 / 2, (int)app->win->GetWindowHeight() / 2 + 140, 190, 40 }, hoverFx, clickFx);
    buttonExit->SetObserver(this);

    buttonReturn = new GuiButton(4, { (int)app->win->GetWindowWidth() / 2 - 190 / 2, 623, 190, 40 }, hoverFx, clickFx);
    buttonReturn->SetObserver(this);

    font = new Font("Assets/Fonts/future_font.xml");

    buttonStart->SetTexture(atlasGUITexture);
    buttonCredits->SetTexture(atlasGUITexture);
    buttonExit->SetTexture(atlasGUITexture);
    buttonReturn->SetTexture(atlasGUITexture);

    app->audio->PlayMusic("Assets/Audio/Music/menu.wav");

    return false;
}

bool SceneTitle::Update(float dt)
{
    if (menuCurrentSelection == MenuSelection::NONE)
    {
        buttonStart->Update(dt);
        buttonCredits->Update(dt);
        buttonExit->Update(dt);
    }
    else if (menuCurrentSelection == MenuSelection::START)
    {
        TransitionToScene(SceneType::GAMEPLAY);
    }
    else if (menuCurrentSelection == MenuSelection::CREDITS)
    {
        buttonReturn->Update(dt);
    }
    else if (menuCurrentSelection == MenuSelection::EXIT)
    {
        app->sceneManager->menuExitCall = true;
    }

    if (app->input->GetKey(SDL_SCANCODE_B) == KEY_DOWN)
        menuCurrentSelection = MenuSelection::NONE;

    app->input->GetMousePosition(mousePos.x, mousePos.y);

    if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
        clicking = true;
    else
        clicking = false;

    if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
        TransitionToScene(SceneType::GAMEPLAY);

    return false;
}

bool SceneTitle::Draw()
{
    int offset = 3;
    if (menuCurrentSelection == MenuSelection::NONE)
    {
        buttonStart->Draw();
        buttonCredits->Draw();
        buttonExit->Draw();

        app->render->DrawText(font, "APOLLO MISSION", (int)app->win->GetWindowWidth() / 4 + offset, (int)app->win->GetWindowHeight() / 2 - 100 + offset, 75, 13, { 105,105,105,255 });
        app->render->DrawText(font, "APOLLO MISSION", (int)app->win->GetWindowWidth() / 4, (int)app->win->GetWindowHeight() / 2 - 100, 75, 13, { 255,255,255,255 });

        app->render->DrawText(font, "START", (int)app->win->GetWindowWidth() / 2 - 65 + offset, (int)app->win->GetWindowHeight() / 2 + 23 + offset, 40, 5, { 105,105,105,255 });
        app->render->DrawText(font, "START", (int)app->win->GetWindowWidth() / 2 - 65, (int)app->win->GetWindowHeight() / 2 + 23, 40, 5, { 255,255,255,255 });

        app->render->DrawText(font, "CREDITS", (int)app->win->GetWindowWidth() / 2 - 83 + offset, (int)app->win->GetWindowHeight() / 2 + 83 + offset, 40, 5, { 105,105,105,255 });
        app->render->DrawText(font, "CREDITS", (int)app->win->GetWindowWidth() / 2 - 83, (int)app->win->GetWindowHeight() / 2 + 83, 40, 5, { 255,255,255,255 });

        app->render->DrawText(font, "EXIT", (int)app->win->GetWindowWidth() / 2 - 43 + offset, (int)app->win->GetWindowHeight() / 2 + 143 + offset, 40, 5, { 105,105,105,255 });
        app->render->DrawText(font, "EXIT", (int)app->win->GetWindowWidth() / 2 - 43, (int)app->win->GetWindowHeight() / 2 + 143, 40, 5, { 255,255,255,255 });
    }
    else if (menuCurrentSelection == MenuSelection::CREDITS)
    {
        app->render->DrawText(font, "AUTHORS:", 150 + offset, 130 + offset, 30, 5, { 105,105,105,255 });
        app->render->DrawText(font, "AUTHORS:", 150, 130, 30, 5, { 255,255,255,255 });
        app->render->DrawText(font, "ALEJANDRO AVILA", 150 + offset, 170 + offset, 30, 5, { 105,105,105,255 });
        app->render->DrawText(font, "ALEJANDRO AVILA", 150, 170, 30, 5, { 255,255,255,255 });
        app->render->DrawText(font, "BOSCO BARBER", 150 + offset, 210 + offset, 30, 5, { 105,105,105,255 });
        app->render->DrawText(font, "BOSCO BARBER", 150, 210, 30, 5, { 255,255,255,255 });
        app->render->DrawText(font, "YERAY TARIFA", 150 + offset, 250 + offset, 30, 5, { 105,105,105,255 });
        app->render->DrawText(font, "YERAY TARIFA", 150, 250, 30, 5, { 255,255,255,255 });

        offset = 2;
        app->render->DrawText(font, "This project is licensed under an unmodified MIT license, which is an OSI-", 150 + offset, 380 + offset, 25, 3, { 105,105,105,255 });
        app->render->DrawText(font, "This project is licensed under an unmodified MIT license, which is an OSI-", 150, 380, 25, 3, { 255,255,255,255 });
        app->render->DrawText(font, "-certified license that allows static linking with closed source software.", 150 + offset, 410 + offset, 25, 3, { 105,105,105,255 });
        app->render->DrawText(font, "-certified license that allows static linking with closed source software.", 150, 410, 25, 3, { 255,255,255,255 });
        app->render->DrawText(font, "The assets' work of this project is licensed under the Creative Commons", 150 + offset, 470 + offset, 25, 3, { 105,105,105,255 });
        app->render->DrawText(font, "The assets' work of this project is licensed under the Creative Commons", 150, 470, 25, 3, { 255,255,255,255 });
        app->render->DrawText(font, "Attribution 4.0 International License.", 150 + offset, 500 + offset, 25, 3, { 105,105,105,255 });
        app->render->DrawText(font, "Attribution 4.0 International License.", 150, 500, 25, 3, { 255,255,255,255 });

        offset = 3;
        buttonReturn->Draw();
        app->render->DrawText(font, "RETURN", (int)app->win->GetWindowWidth() / 2 - 80 + offset, 625 + offset, 40, 5, { 105,105,105,255 });
        app->render->DrawText(font, "RETURN", (int)app->win->GetWindowWidth() / 2 - 80, 625, 40, 5, { 255,255,255,255 });
    }

    if (clicking)
        app->render->DrawTextureWithoutCamera(atlasGUITexture, mousePos.x, mousePos.y, &mouseCursorRect[0]);
    else
        app->render->DrawTextureWithoutCamera(atlasGUITexture, mousePos.x, mousePos.y, &mouseCursorRect[1]);

    return false;
}

bool SceneTitle::Unload()
{
    app->tex->UnLoad(atlasGUITexture);
    atlasGUITexture = nullptr;

    delete buttonStart;
    delete buttonCredits;
    delete buttonExit;
    delete buttonReturn;

    delete font;

    return false;
}

//----------------------------------------------------------
// Manage GUI events for this screen
//----------------------------------------------------------
bool SceneTitle::OnGuiMouseClickEvent(GuiControl* control)
{
    if (control->type == GuiControlType::BUTTON)
    {
        if (control->id == 1) menuCurrentSelection = MenuSelection::START;
        else if (control->id == 2) menuCurrentSelection = MenuSelection::CREDITS;
        else if (control->id == 3) menuCurrentSelection = MenuSelection::EXIT;
        else if (control->id == 4) menuCurrentSelection = MenuSelection::NONE;
    }

    return true;
}