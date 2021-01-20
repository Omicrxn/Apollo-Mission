
#include "Body.h"
#include "Shape.h"
Body::Body(float density, Shape* shape)
{
	this->shape = shape;
	this->shape->SetDensity(density);
	this->mass = this->shape->GetMass();
	this->inertia = this->shape->GetInertia();

}

void Body::Update(float dt) {

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
	return force / mass + gravity;
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

void Body::AddForce(Vec2f force, Vec2f position)
{
	this->AddForce(force);
	this->AddTorque(position.Cross(force));
}

void Body::AddImpulse(Vec2f impulse, Vec2f position)
{
	this->velocity += impulse * mass;
	this->angularVelocity += position.Cross(impulse) * this->inertia;
}