#include "Physics.h"

Physics* Physics::instance = nullptr;

Physics* Physics::GetInsance()
{
	if (instance == nullptr) instance = new Physics();
	return instance;
}

Physics::Physics() {}
Physics::~Physics()
{
	RELEASE(instance);
}

void Physics::UpdateVelocity(iPoint& position, fPoint& velocity, float& acceleration, float dt)
{
	position.x = position.x + velocity.x * dt;
	position.y = position.y + velocity.y * dt + (GRAVITY * dt * dt * 0.5);
	velocity.y = velocity.y + GRAVITY * dt;
}

fPoint Physics::AccelerationFromForce(fPoint force, uint mass)
{
	
	return fPoint(force.x / mass, force.y / mass);
}
