#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include "Module.h"
#include "Scene.h"

class SceneManager : public Module
{
public:

	SceneManager();

	// Destructor
	virtual ~SceneManager();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

public:

	bool menuExitCall = false;
	bool win = false;

private:
	
	Scene* current = nullptr;
	Scene* next = nullptr;

	// Required variables to manage screen transitions (fade-in, fade-out)
	bool onTransition = false;
	bool fadeOutCompleted = false;
	float transitionAlpha = 0.0f;
};

#endif // __SCENEMANAGER_H__