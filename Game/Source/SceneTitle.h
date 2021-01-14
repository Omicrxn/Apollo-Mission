#ifndef __SCENETITLE_H__
#define __SCENETITLE_H__

#include "Scene.h"

#include "GuiButton.h"

class Font;

enum class MenuSelection
{
    NONE,
    START,
    CREDITS,
    EXIT
};

class SceneTitle : public Scene
{
public:

    SceneTitle();
    virtual ~SceneTitle();

    bool Load();

    bool Update(float dt);

    bool Draw();

    bool Unload();

    // Declare on mouse click event
    bool OnGuiMouseClickEvent(GuiControl* control);

private:

    SDL_Texture* atlasGUITexture = nullptr;

    GuiButton* btnStart = nullptr;
    GuiButton* btnExit = nullptr;
    GuiButton* btnCredits = nullptr;

    MenuSelection menuCurrentSelection = MenuSelection::NONE;

    iPoint mousePos = { 0,0 };
    bool clicking = false;
    int hoverFx = -1;
    int clickFx = -1;

    SDL_Rect mouseCursorRect[2] = { 0,0,0,0 };

    Font* font = nullptr;
};

#endif // __SCENETITLE_H__