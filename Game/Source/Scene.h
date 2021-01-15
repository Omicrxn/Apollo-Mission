#ifndef __SCENE_H__
#define __SCENE_H__

#include "SString.h"

class GuiControl;

enum class SceneType
{
    LOGO,
    TITLE,
    GAMEPLAY
};

class Scene
{
public:

    Scene() : active(true), loaded(false), transitionRequired(false) {}

    virtual bool Load()
    {
        return true;
    }

    virtual bool Update(float dt)
    {
        return true;
    }

    virtual bool Draw()
    {
        return true;
    }

    virtual bool Unload()
    {
        return true;
    }

    void TransitionToScene(SceneType scene)
    {
        transitionRequired = true;
        nextScene = scene;
    }

    // Define multiple Gui Event methods
    virtual bool OnGuiMouseClickEvent(GuiControl* control)
    {
        return true;
    }

public:

    bool active = true;

    // Possible properties
    bool loaded = false;

    // Transition animation properties
    bool transitionRequired = false;
    SceneType nextScene;
};

#endif // __SCENE_H__