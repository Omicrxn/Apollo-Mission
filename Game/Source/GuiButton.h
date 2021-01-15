#ifndef __GUIBUTTON_H__
#define __GUIBUTTON_H__

#include "GuiControl.h"

#include "Point.h"

class GuiButton : public GuiControl
{
public:

    GuiButton(uint32 id, SDL_Rect bounds, int hoverFx, int clickFx);
    virtual ~GuiButton();

    bool Update(float dt);
    bool Draw();

private:

    // Gui Button specific properties
    // Maybe some animation properties for state change?
    SDL_Rect whiteButton = { 0,0,0,0 };
    SDL_Rect brownButton = { 0,0,0,0 };
    SDL_Rect greyButton = { 0,0,0,0 };
    SDL_Rect yellowButton = { 0,0,0,0 };

    int hoverFx = -1;
    int clickFx = -1;

    bool isFocusing = false;
};

#endif // __GUIBUTTON_H__
