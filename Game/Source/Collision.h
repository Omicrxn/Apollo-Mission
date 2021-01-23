#include "SDL/include/SDL_Rect.h"
#include "CustomMath.h"
#include "Point.h"
#include "Module.h"
#include "List.h"
#define MAX_COLLIDERS 50
enum class ColliderType {
	NONE = -1,
	CIRCLE,
	RECTANGLE,
	MAX
};
struct CircleCollider {
	iPoint position = { 0,0 };
	float radius = 0.0f;
};
class CircleCollision
{
public:

	CircleCollider collider;
	Module* listener;
	CircleCollision(float x, float y, float radius, Module* listener = nullptr);
	bool Intersects(CircleCollider& colliderB);
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
	bool Intersects(CircleCollider& colliderB);
	void SetPosition(Vec2f position);

};