#pragma once
#include "Module.h"
#include "Point.h"

#define GRAVITY 600.0f
class Physics : public Module
{
public:
	static Physics* GetInsance();
	~Physics();

	void UpdateVelocity(iPoint& position, fPoint& velocity, float& acceleration, float dt);

	void EulerIntegrator();

	fPoint AccelerationFromForce(fPoint force, uint mass);

private:
	static Physics* instance;
	Physics();
	Physics(const Physics&);
	Physics& operator=(const Physics&);
	
};