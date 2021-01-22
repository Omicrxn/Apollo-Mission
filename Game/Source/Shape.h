#pragma once
#include "Vec2.h"
#define PI 3.14159265358979323846
class Shape {
public:
	float density = 0;
	float mass = 0;
	float inertia = 0;

	virtual void SetMass()
	{
		this->mass = 0;
	}
	virtual void SetInertia()
	{
		this->inertia = 0;
	}
	virtual void SetDensity(float density)
	{
		this->density = density;
	}
	virtual float GetMass()
	{
		return this->mass;
	}
	virtual float GetInertia()
	{
		return this->inertia;
	}
	virtual float GetDensity()
	{
		return this->density;
	}
};