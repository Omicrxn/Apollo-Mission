#include "SDL/include/SDL_Rect.h"
#include "Point.h"
struct Module;

class CircleCollision
{
public:
	struct Circle {
		iPoint position = { 0,0 };
		float radius = 0.0f;
	};
	Circle collider;
	CircleCollision(float x, float y, float radius);
	bool Intersects(CircleCollision& colliderB);
	bool Intersects(SDL_Rect& colldierB);
	void SetPosition(iPoint position);
};
class RectCollision
{
public:
	RectCollision(SDL_Rect rectangle, Module* listener = nullptr);
	SDL_Rect collider;
	Module* listener;
	bool Intersects(SDL_Rect& colliderB);
	bool Intersects(CircleCollision& colliderB);
	void SetPosition(iPoint position);
};
