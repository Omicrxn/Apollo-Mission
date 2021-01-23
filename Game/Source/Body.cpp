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
	printf("%f\n", velocity.y);
}

void Body::EulerIntegratorAngular(float dt) {
	float angularAcceleration = AccelerationFromForceAngular(torque, mass);
	angularVelocity += (angularAcceleration * dt);
	rotation += (angularAcceleration * dt);

}

Vec2f Body::AccelerationFromForce(Vec2f force, float mass)
{


	return force / mass; //TODO: Check if dt
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

void Body::AddBuoyancy()
{
	/*Vec2f buoyantForce = -fluidDensity * gravity * fluidVolume;
	this->force += buoyantForce;*/
}

void Body::AddLift(float atmosphereDensity, float wingSurface)
{
	Vec2f liftForce = Vec2f::Pow(velocity) * atmosphereDensity * wingSurface * liftCoeficient;
}

void Body::AddCollision(SDL_Rect bounds, CollisionType type, Module* listener) {

	switch (type)
	{
	case CollisionType::CIRCLE:
		this->circleCollision = new CircleCollision(bounds.x,bounds.y,bounds.w,listener);
		break;
	case CollisionType::RECTANGLE:
		this->rectCollision = new RectCollision(bounds, listener);
		break;
	case CollisionType::NONE:
		break;
	default:
		break;
	}

}