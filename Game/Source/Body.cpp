#include <cmath>
#include "Body.h"
#include "Shape.h"

Body::Body(Vec2f position, float density, Shape* shape, float dragCoeficient)
{
	this->shape = shape;
	this->shape->body = this;
	this->position = position;
	this->dragCoeficient = dragCoeficient;
	this->velocity.Set(0, 0);
	this->angularVelocity = 0;
	this->torque = 0;
	this->force.Set(0, 0);
	this->restitutionCoeficient = 0.2f;
	this->shape->Initialize(density);
}

void Body::Update(float dt) {
	AddDrag();
	EulerIntegrator(dt);
	EulerIntegratorAngular(dt);
	//clear force and torque so that there are no leaks in the next timestamp
	force.Set(0,0);
	torque = 0;
}

void Body::EulerIntegrator(float dt) {
	Vec2f acceleration = AccelerationFromForce(force, mass);
	velocity += acceleration * dt;
	position += velocity * dt;
}

void Body::EulerIntegratorAngular(float dt) {
	float angularAcceleration = AccelerationFromForceAngular(torque, mass);
	angularVelocity += (angularAcceleration * dt);
	rotation += (angularAcceleration * dt);

}

Vec2f Body::AccelerationFromForce(Vec2f force, float mass)
{


	return force / mass;
}

float Body::AccelerationFromForceAngular(float torque, float inertia)
{
	return torque / inertia;
}

void Body::AddForce(Vec2f force)
{
	this->force += force;
}

void Body::AddTorque(float torque)
{
	this->torque += torque;
}

void Body::AddForceAndTorque(Vec2f force, Vec2f position)
{
	this->AddForce(force);
	this->AddTorque(position.Cross(force));
}

void Body::AddImpulse(Vec2f impulse, Vec2f position)
{
	this->velocity += impulse * mass;
	this->angularVelocity += position.Cross(impulse) * this->inertia;
}
Vec2f Body::GetGravity(Vec2f maxGravity, Vec2f position, uint gravityStart, uint gravityEnd, bool up)
{
	if (position.y > gravityStart && position.y < gravityEnd)
	{
		Vec2f gravity = { 0.0f,0.0f };
		if (up)
		{
			gravity.y = maxGravity.y - ((maxGravity.y / (gravityEnd - gravityStart)) * (position.y - gravityStart));
		}
		else
		{
			gravity.y = maxGravity.y - ((maxGravity.y / (gravityEnd - gravityStart)) * (gravityEnd - position.y));
		}
		return gravity;
	}
	
	return Vec2f{ 0.0f,0.0f };
}
void Body::AddGravity(Vec2f gravity) {
	Vec2f gravityForce =  gravity * mass;
	this->AddForce(gravityForce);
}

void Body::AddNormalForce(Vec2f gravity) {
	Vec2f normalForce = gravity * mass;
	this->AddForce(normalForce);

}
void Body::AddDrag()
{
	Vec2f dir;
	if (velocity.x > 0)
		dir.x = -1;
	else
		dir.x = 1;
	
	if (velocity.y > 0)
		dir.y = -1;
	else
		dir.y = 1;
	Vec2f dragForce = Vec2f::Pow(velocity) * 0.5f  * shape->area * dir * dragCoeficient;
	AddForce(dragForce);
}

float Body::GetBuoyancyHeight(Vec2f position, uint buoyancyStart, uint buoyancyEnd)
{
	return (position.y - buoyancyStart) * 0.1;
}
void Body::AddBuoyancy(float fluidDensity, Vec2f gravity, float volumeSubmerged, float buoyancyHeight)
{
	Vec2f buoyantForce = gravity * -fluidDensity * volumeSubmerged * buoyancyHeight;
	this->force += buoyantForce;
}

void Body::AddLift(float atmosphereDensity, float wingSurface)
{
	Vec2f liftForce = Vec2f::Pow(velocity) * atmosphereDensity * wingSurface * liftCoeficient;
}

void Body::AddCollision(SDL_Rect bounds, ColliderType type, Module* listener) {

	switch (type)
	{
	case ColliderType::CIRCLE:
		
		this->circleCollision = new CircleCollision(bounds.x,bounds.y,bounds.w,listener);
		break;
	case ColliderType::RECTANGLE:
		this->rectCollision = new RectCollision(bounds, listener);
		break;
	case ColliderType::NONE:
		break;
	default:
		break;
	}
}

void Body::CleanUp() {
	RELEASE(rectCollision);
	RELEASE(circleCollision);
	RELEASE(shape);
}