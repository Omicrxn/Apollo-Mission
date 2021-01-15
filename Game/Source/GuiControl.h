#ifndef __GUICONTROL_H__
#define __GUICONTROL_H__

#include "Scene.h"

#include "Point.h"

#include "SDL/include/SDL.h"

enum class GuiControlType
{
    BUTTON,
    NONE
};

enum class GuiControlState
{
    DISABLED,
    NORMAL,
    FOCUSED,
    PRESSED
};

class GuiControl
{
public:

    GuiControl(GuiControlType type, uint32 id) : type(type), id(id), state(GuiControlState::NORMAL) {}

    GuiControl(GuiControlType type, SDL_Rect bounds) :
        type(type),
        state(GuiControlState::NORMAL),
        bounds(bounds)
    {
        texture = NULL;
    }

    virtual bool Update(float dt)
    {
        return true;
    }

    virtual bool Draw() const
    {
        return true;
    }

    void SetTexture(SDL_Texture* tex)
    {
        texture = tex;
    }

    void SetObserver(Scene* module)
    {
        observer = module;
    }

    void NotifyObserver()
    {
        observer->OnGuiMouseClickEvent(this);
    }

public:

    uint32 id;
    GuiControlType type = GuiControlType::NONE;
    GuiControlState state = GuiControlState::NORMAL;

    SDL_Rect bounds = { 0,0,0,0 };     // Position and size

    SDL_Texture* texture = nullptr;   // Texture atlas reference

    Scene* observer = nullptr;        // Observer module (it should probably be an array/list)
};

#endif // __GUICONTROL_H__