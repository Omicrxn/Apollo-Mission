#pragma once
#include "Vec2.h"

#include "Point.h"
class Shape;
class Body {
public:
	Vec2f position = Vec2<float>(0,0);
	float rotation = 0.0f;

	Vec2f velocity = Vec2<float>(0.0f, 0.0f);
	float angularVelocity = 0.0f;

	Vec2f force = Vec2<float>(0.0f, 0.0f);
	float torque = 0.0f;

	float mass = 0.0f;
	float inertia = 0.0f;

	float dragCoeficient = 0.0f;
	float liftCoeficient = 0.0f;

	Shape* shape;

	Vec2f gravity = Vec2f(0.0f,600.0f);

	Body(float density, Shape* shape, float dragCoeficient);
	void Update(float dt);

	void AddImpulse(Vec2f impulse, Vec2f position);
	void AddForce(Vec2f force);
	void AddTorque(float torque);
	void AddForceAndTorque(Vec2f force, Vec2f position);
	void AddBuoyancy();
	void AddDrag();
	void AddLift(float atmosphereDensity, float surface);
private:

	void EulerIntegrator(float dt);
	void EulerIntegratorAngular(float dt);

	Vec2f AccelerationFromForce(Vec2f force, float mass);
	float AccelerationFromForceAngular(float torque, float inertia);
};