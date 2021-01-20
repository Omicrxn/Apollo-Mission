#pragma once
#include "Shape.h"
class CircleShape : Shape {
	float radius = 0;
public:
	CircleShape(float radius)
	{
		this->radius = radius;
	}
	void SetDensity(float density)
	{
		this->density = density;
		SetMass();
		SetInertia();
	}

	void SetMass()
	{
		mass = density * PI * radius * radius;
	}
	void SetInertia() 
	{
		inertia = 0.5 * mass * radius * radius;
	}

};