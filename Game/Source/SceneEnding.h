#ifndef __SCENEENDING_H__
#define __SCENEENDING_H__

#include "Scene.h"

class SceneEnding : public Scene
{
public:

    SceneEnding();
    virtual ~SceneEnding();

    bool Load();

    bool Update(float dt);

    bool Draw();

    bool Unload();

private:
};

#endif // __SCENEENDING_H__