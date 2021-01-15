#include "GuiButton.h"

#include "App.h"
#include "Render.h"
#include "Input.h"
#include "Audio.h"

GuiButton::GuiButton(uint32 id, SDL_Rect bounds, int hoverFx, int clickFx) : GuiControl(GuiControlType::BUTTON, id)
{
    this->bounds = bounds;
    this->hoverFx = hoverFx;
    this->clickFx = clickFx;

    whiteButton = { 0,0,190,49 };
    brownButton = { 0,49,190,49 };
    greyButton = { 0,188,190,49 };
    yellowButton = { 0,282,190,49 };
    
    isFocusing = false;
}

GuiButton::~GuiButton()
{
}

bool GuiButton::Update(float dt)
{
    if (state != GuiControlState::DISABLED)
    {
        int mouseX, mouseY;
        app->input->GetMousePosition(mouseX, mouseY);

        // Check collision between mouse and button bounds
        if ((mouseX > bounds.x) && (mouseX < (bounds.x + bounds.w)) && 
            (mouseY > bounds.y) && (mouseY < (bounds.y + bounds.h)))
        {
            state = GuiControlState::FOCUSED;

            if (!isFocusing)
            {
                isFocusing = true;
                app->audio->PlayFx(hoverFx);
            }

            if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
            {
                state = GuiControlState::PRESSED;
            }

            if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_DOWN)
            {
                state = GuiControlState::PRESSED;
                app->audio->PlayFx(clickFx);
            }

            // If mouse button pressed -> Generate event!
            if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
            {
                NotifyObserver();
            }
        }
        else
        {
            state = GuiControlState::NORMAL;
            isFocusing = false;
        }
    }

    return false;
}

bool GuiButton::Draw()
{
    // Draw the right button depending on state
    switch (state)
    {
    case GuiControlState::DISABLED: 
        app->render->DrawTextureWithoutCamera(texture, bounds.x, bounds.y, &whiteButton);
        break;
    case GuiControlState::NORMAL: 
        app->render->DrawTextureWithoutCamera(texture, bounds.x, bounds.y, &greyButton);
        break;
    case GuiControlState::FOCUSED: 
        app->render->DrawTextureWithoutCamera(texture, bounds.x, bounds.y, &yellowButton);
        break;
    case GuiControlState::PRESSED: 
        app->render->DrawTextureWithoutCamera(texture, bounds.x, bounds.y, &whiteButton);
        break;
    default:
        break;
    }

    return false;
}