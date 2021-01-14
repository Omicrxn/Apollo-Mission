#ifndef __GUIBUTTON_H__
#define __GUIBUTTON_H__

#include "GuiControl.h"

#include "Audio.h"

#include "Point.h"
#include "SString.h"

class GuiButton : public GuiControl
{
public:

    GuiButton(uint32 id, SDL_Rect bounds, const char *text);
    virtual ~GuiButton();

    bool Update(float dt);
    bool Draw();

private:

    // Gui Button specific properties
    // Maybe some animation properties for state change?
    SDL_Rect whiteButton = { 0,0,190,49 };
    SDL_Rect brownButton = { 0,49,190,49 };
    SDL_Rect greyButton = { 0,188,190,49 };
    SDL_Rect yellowButton = { 0,282,190,49 };

    bool isFocusing = false;
};

#endif // __GUIBUTTON_H__
