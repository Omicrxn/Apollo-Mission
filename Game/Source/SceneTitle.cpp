#include "SceneTitle.h"

#include "App.h"
#include "Render.h"
#include "Input.h"
#include "Window.h"
#include "Textures.h"
#include "Font.h"

#include "EntityManager.h"

#include "SDL/include/SDL.h"

SceneTitle::SceneTitle()
{
    // GUI: Initialize required controls for the screen
    btnStart = new GuiButton(1, { (int)app->win->GetWindowWidth() / 2 - 190 / 2, (int)app->win->GetWindowHeight() / 2 + 20, 190, 40 }, "START");
    btnStart->SetObserver(this);

    btnCredits = new GuiButton(2, { (int)app->win->GetWindowWidth() / 2 - 190 / 2, (int)app->win->GetWindowHeight() / 2 + 80, 190, 40 }, "CREDITS");
    btnCredits->SetObserver(this);

    btnExit = new GuiButton(3, { (int)app->win->GetWindowWidth() / 2 - 190 / 2, (int)app->win->GetWindowHeight() / 2 + 140, 190, 40 }, "EXIT");
    btnExit->SetObserver(this);

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
    font = new Font("Assets/Fonts/future_font.xml");

    btnStart->SetTexture(atlasGUITexture);
    btnCredits->SetTexture(atlasGUITexture);
    btnExit->SetTexture(atlasGUITexture);

    app->audio->PlayMusic("Assets/Audio/Music/music_spy.ogg");

    return false;
}

bool SceneTitle::Update(float dt)
{
    if (menuCurrentSelection == MenuSelection::NONE)
    {
        //btnStart->Update(dt, hoverFx, clickFx);
        //btnCredits->Update(dt, hoverFx, clickFx);
        //btnExit->Update(dt, hoverFx, clickFx);
    }
    else if (menuCurrentSelection == MenuSelection::START)
    {
        TransitionToScene(SceneType::GAMEPLAY);
    }
    else if (menuCurrentSelection == MenuSelection::EXIT)
    {
        //app->sceneManager->menuExitCall = true;
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
        btnStart->Draw();
        btnCredits->Draw();
        btnExit->Draw();

        app->render->DrawText(font, "APOLLO MISSION", 370 + offset, 250 + offset, 75, 13, { 105,105,105,255 });
        app->render->DrawText(font, "APOLLO MISSION", 370, 250, 75, 13, { 255,255,255,255 });
    }
    else if (menuCurrentSelection == MenuSelection::CREDITS)
    {
        app->render->DrawText(font, "AUTHORS:", 570 + offset, 190 + offset, 40, 5, { 105,105,105,255 });
        app->render->DrawText(font, "AUTHORS:", 570, 190, 40, 5, { 255,255,255,255 });
        app->render->DrawText(font, "ALEJANDRO AVILA", 490 + offset, 230 + offset, 40, 5, { 105,105,105,255 });
        app->render->DrawText(font, "ALEJANDRO AVILA", 490, 230, 40, 5, { 255,255,255,255 });
        app->render->DrawText(font, "BOSCO BARBER", 520 + offset, 270 + offset, 40, 5, { 105,105,105,255 });
        app->render->DrawText(font, "BOSCO BARBER", 520, 270, 40, 5, { 255,255,255,255 });
        app->render->DrawText(font, "YERAY TARIFA", 520 + offset, 310 + offset, 40, 5, { 105,105,105,255 });
        app->render->DrawText(font, "YERAY TARIFA", 520, 310, 40, 5, { 255,255,255,255 });

        offset = 2;
        app->render->DrawText(font, "This project is licensed under an unmodified MIT license, which is an", 150 + offset, 400 + offset, 30, 3, { 105,105,105,255 });
        app->render->DrawText(font, "This project is licensed under an unmodified MIT license, which is an", 150, 400, 30, 3, { 255,255,255,255 });
        app->render->DrawText(font, "OSI-certified license that allows static linking with closed source software.", 150 + offset, 430 + offset, 30, 3, { 105,105,105,255 });
        app->render->DrawText(font, "OSI-certified license that allows static linking with closed source software.", 150, 430, 30, 3, { 255,255,255,255 });
        app->render->DrawText(font, "The assets' work of this project is licensed under the", 150 + offset, 490 + offset, 30, 3, { 105,105,105,255 });
        app->render->DrawText(font, "The assets' work of this project is licensed under the", 150, 490, 30, 3, { 255,255,255,255 });
        app->render->DrawText(font, "Creative Commons Attribution 4.0 International License.", 150 + offset, 520 + offset, 30, 3, { 105,105,105,255 });
        app->render->DrawText(font, "Creative Commons Attribution 4.0 International License.", 150, 520, 30, 3, { 255,255,255,255 });

        offset = 3;
        app->render->DrawText(font, "PRESS 'B' TO RETURN", 475 + offset, 623 + offset, 40, 5, { 105,105,105,255 });
        app->render->DrawText(font, "PRESS 'B' TO RETURN", 475, 623, 40, 5, { 255,255,255,255 });
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

    delete btnStart;
    delete btnCredits;
    delete btnExit;

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
        else if (control->id == 3) menuCurrentSelection = MenuSelection::EXIT; // TODO: Exit request
    }

    return true;
}