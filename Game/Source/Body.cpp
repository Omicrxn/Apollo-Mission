
#include "Body.h"
#include "Shape.h"
Body::Body(float density, Shape* shape, float dragCoeficient)
{
	this->shape = shape;
	this->shape->SetDensity(density);
	this->mass = this->shape->GetMass();
	this->inertia = this->shape->GetInertia();
	this->dragCoeficient = dragCoeficient;
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
	return force / mass + gravity; //TODO: Check if dt
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
	Vec2f dragForce = Vec2f::Pow(velocity) * 0.5f  * mass * dir * dragCoeficient;
	this->force += dragForce;
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