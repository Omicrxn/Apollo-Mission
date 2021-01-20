#ifndef __RENDER_H__
#define __RENDER_H__

#include "Module.h"

#include "Point.h"
#include "Vec2.h"
#include "Font.h"

#include "SDL/include/SDL.h"

class Render : public Module
{
public:

	Render();

	// Destructor
	virtual ~Render();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Utils
	void SetViewPort(const SDL_Rect& rect);
	void ResetViewPort();
	iPoint ScreenToWorld(int x, int y) const;

	void CameraFollow(Vec2f position);
	// Drawing
	bool DrawTexture(SDL_Texture* texture, int x, int y, const SDL_Rect* section = NULL, float speed = 1.0f, double angle = 0, int pivotX = INT_MAX, int pivotY = INT_MAX, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
	bool DrawRectangle(const SDL_Rect& rect, SDL_Color color, bool filled = true) const;
	bool DrawLine(int x1, int y1, int x2, int y2, SDL_Color color) const;
	bool DrawCircle(int x1, int y1, int redius, SDL_Color color) const;

	bool DrawText(Font* font, const char* text, int x, int y, int size, int spacing, SDL_Color tint);

	bool DrawTextureWithoutCamera(SDL_Texture* texture, int x, int y, const SDL_Rect* section = NULL, float speed = 1.0f, bool isLeft = false, double angle = 0, int pivotX = INT_MAX, int pivotY = INT_MAX) const;

	// Set background color
	void SetBackgroundColor(SDL_Color color);

public:

	SDL_Renderer* renderer = nullptr;
	SDL_Rect camera = { 0,0,0,0 };
	SDL_Rect viewport = { 0,0,0,0 };
	SDL_Color background;

	uint scale = 1;
};

#endif // __RENDER_H__