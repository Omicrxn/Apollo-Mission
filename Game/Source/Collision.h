#include "SDL/include/SDL_Rect.h"
#include "CustomMath.h"
#include "Point.h"
#include "Module.h"

enum class CollisionType {
	CIRCLE,
	RECTANGLE,
	NONE
};
class CircleCollision
{
public:
	struct Circle {
		iPoint position = { 0,0 };
		float radius = 0.0f;
	};
	Circle collider;
	Module* listener;
	CircleCollision(float x, float y, float radius, Module* listener = nullptr);
	bool Intersects(CircleCollision& colliderB);
	bool Intersects(SDL_Rect& colldierB);
	void SetPosition(Vec2f position);
};
class RectCollision
{
public:
	RectCollision(SDL_Rect rectangle, Module* listener = nullptr);
	SDL_Rect collider;
	Module* listener;
	bool Intersects(SDL_Rect& colliderB);
	bool Intersects(CircleCollision& colliderB);
	void SetPosition(Vec2f position);
};
