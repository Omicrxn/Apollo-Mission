#include "Collider.h"
#include "Module.h"

RectCollision::RectCollision(SDL_Rect collider, Module* listener) {
	this->collider = collider;
	this->listener = listener;
}

bool RectCollision::Intersects(SDL_Rect& colliderB) {

	return (collider.x < colliderB.x + colliderB.w &&
		collider.x + collider.w > colliderB.x &&
		collider.y < colliderB.y + colliderB.h &&
		collider.y + collider.h > colliderB.y);
}

bool RectCollision::Intersects(CircleCollision& colliderB) {
	iPoint closestPoint = { 0,0 };
	if (colliderB.collider.position.x < collider.x)
	{
		closestPoint.x = collider.x;
	}
	else if (colliderB.collider.position.x > collider.x + collider.w)
	{
		closestPoint.x = collider.x + collider.w;
	}
	else
	{
		closestPoint.x = colliderB.collider.position.x;
	}

	if (colliderB.collider.position.y < collider.y)
	{
		closestPoint.y = collider.y;
	}
	else if (colliderB.collider.position.y > collider.y + collider.h)
	{
		closestPoint.y = collider.y + collider.h;
	}
	else
	{
		closestPoint.y = colliderB.collider.position.y;
	}
	iPoint colliderAPos = { collider.x,collider.y };
	int distance = colliderAPos.DistanceTo(closestPoint);
	if (distance < colliderB.collider.radius) {
		return true;
	}
	return false;
}

void RectCollision::SetPosition(iPoint position) {
	this->collider.x = position.x;
	this->collider.y = position.y;
}


CircleCollision::CircleCollision(float x, float y, float radius) {
	this->collider.position.x = x;
	this->collider.position.y = y;
	this->collider.radius = radius;
}

bool CircleCollision::Intersects(CircleCollision& colliderB) {
	return this->collider.position.DistanceTo(colliderB.collider.position) < (this->collider.radius + colliderB.collider.radius);
}

bool CircleCollision::Intersects(SDL_Rect& colliderB) {
	iPoint closestPoint = { 0,0 };
	if ( this->collider.position.x < colliderB.x)
	{
		closestPoint.x = colliderB.x;
	}
	else if (this->collider.position.x > colliderB.x + colliderB.w)
	{
		closestPoint.x = colliderB.x + colliderB.w;
	}
	else
	{
		closestPoint.x = this->collider.position.x;
	}

	if (this->collider.position.y< colliderB.y)
	{
		closestPoint.y = colliderB.y;
	}
	else if (this->collider.position.y > colliderB.y + colliderB.h)
	{
		closestPoint.y = colliderB.y + colliderB.h;
	}
	else
	{
		closestPoint.y = this->collider.position.y;
	}
;
	int distance = this->collider.position.DistanceTo(closestPoint);
	if (distance < this->collider.radius) {
		return true;
	}
	return false;
}