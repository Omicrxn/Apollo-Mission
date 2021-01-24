#pragma once
#include "List.h"
#include "Body.h"
class World {
public:
	List<Body*> bodies;
	
	void AddBody(Body* body)
	{
		this->bodies.Add(body);
	}

	void Update(float dt) {
		for (int i = 0; i < bodies.Count(); i++)
		{
			bodies.At(i)->data->Update(dt);
		}
	}
	void CleanUp() {
		for (int i = 0; i < bodies.Count(); i++)
		{
			RELEASE(bodies.At(i)->data);
		}
		bodies.Clear();
	}
};