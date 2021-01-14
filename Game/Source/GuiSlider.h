#ifndef __GUISLIDER_H__
#define __GUISLIDER_H__

#include "GuiControl.h"

#include "Point.h"
#include "SString.h"

class GuiSlider : public GuiControl
{
public:

    GuiSlider(uint32 id, SDL_Rect bounds, const char *text);
    virtual ~GuiSlider();

    bool Update(float dt);
    bool Draw();

private:

    // GuiSlider specific properties
    // Maybe some animation properties for state change?
    SDL_Rect slider = { 0,0,0,0 };;
    int value = 0;

    int minValue = 0;
    int maxValue = 0;
};

#endif // __GUISLIDER_H__