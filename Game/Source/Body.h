#pragma once
#include "CustomMath.h"
#include "Point.h"
#include "Collision.h"
class Shape;

class Body {
public:
	Vec2f position = Vec2f(0,0);
	float rotation = 0.0f;

	Vec2f velocity = Vec2f(0.0f, 0.0f);
	float angularVelocity = 0.0f;

	Vec2f force = Vec2f(0.0f, 0.0f);
	float torque = 0.0f;

	float mass = 0.0f;
	float inv_mass = 0.0f;
	float inertia = 0.0f;
	float inv_inertia = 0.0f;

	float dragCoeficient = 0.0f;
	float liftCoeficient = 0.0f;
	float restitutionCoeficient = 0.0f;
	Shape* shape;
	RectCollision* rectCollision;
	CircleCollision* circleCollision;

	Body(Vec2f position, float density, Shape* shape, float dragCoeficient);
	void Update(float dt);

	void AddImpulse(Vec2f impulse, Vec2f position);
	void AddForce(Vec2f force);
	void AddTorque(float torque);
	void AddForceAndTorque(Vec2f force, Vec2f position);
	float GetBuoyancyHeight(Vec2f position, uint buoyancyStart, uint buoyancyEnd);
	void AddBuoyancy(float fluidDensity, Vec2f gravity, float volumeSubmerged, float buoyancyHeight);
	void AddDrag();
	Vec2f Body::GetGravity(Vec2f maxGravity, Vec2f position, uint gravityStart, uint gravityEnd, bool up);
	void AddGravity(Vec2f gravity);
	void AddNormalForce(Vec2f gravity);
	void AddLift(float atmosphereDensity, float surface);
	void AddCollision(SDL_Rect bounds, ColliderType type, Module* listener = nullptr);
	void CleanUp();
private:

	void EulerIntegrator(float dt);
	void EulerIntegratorAngular(float dt);

	Vec2f AccelerationFromForce(Vec2f force, float mass);
	float AccelerationFromForceAngular(float torque, float inertia);
};