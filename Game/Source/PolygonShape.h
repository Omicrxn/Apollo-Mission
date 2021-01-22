#pragma once
#include "Shape.h"
#include "List.h"
class PolygonShape : Shape {
public:
	List<Vec2f> vertices;
	List<Vec2f> normals;
	Vec2f centroid = Vec2f(0.0f, 0.0f);
	float area = 0.0f;
	PolygonShape(List<Vec2f> vertices)
	{
		for (int i = 0; i < this->vertices.Count(); i++)
		{
			ListItem<Vec2f>* firstPoint = vertices.At(i);
			ListItem<Vec2f>* secondPoint = vertices.At(i + 1);

			float faceArea = 0.5 * abs(firstPoint->data.Cross(secondPoint->data));
			centroid += (firstPoint->data + secondPoint->data) * faceArea / (3.0f * area);

			firstPoint->data -= centroid;
		}
	}
	void SetDensity(float density)
	{
		this->density = density;
		SetMass();
		SetInertia();
	}

	void SetMass()
	{
		float area = 0;
		for (int i = 0; i < this->vertices.Count(); i++)
		{
			ListItem<Vec2f>* firstPoint = vertices.At(i);
			ListItem<Vec2f>* secondPoint = vertices.At(i+1);

			area += 0.5 * abs(firstPoint->data.Cross(secondPoint->data));
			mass = density * area;

		}
	}

	void SetInertia()
	{
		for (int i = 0; i < this->vertices.Count(); i++)
		{
			ListItem<Vec2f>* firstPoint = vertices.At(i);
			ListItem<Vec2f>* secondPoint = vertices.At(i + 1);

			inertia += area * firstPoint->data.Length() + secondPoint->data.Length() + firstPoint->data.Dot(secondPoint) / 6.0f;

		}
	}
};