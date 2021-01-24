#ifndef SHAPE_H
#define SHAPE_H

#include "Body.h"

#define MaxPolyVertexCount 64

struct Shape
{
    enum Type
    {
        CIRCLE_SHAPE,
        POLYGON_SHAPE,
        COUNT
    };

    Shape() {}
    virtual void Initialize(float density) = 0;
    virtual void ComputeMass(customFloat density) = 0;
    virtual Type GetType() const = 0;

    Body* body;
    customFloat area;
    customFloat radius;
};

struct Circle : public Shape
{
public:
    Circle(customFloat r)
    {
        radius = r;
        area = PI * r * r;
    }
    void Initialize(float density)
    {
        ComputeMass(density);
    }

    void ComputeMass(customFloat density)
    {
        body->mass = PI * radius * radius * density;
        body->inv_mass = (body->mass) ? 1.0f / body->mass : 0.0f;
        body->inertia = body->mass * radius * radius;
        body->inv_inertia = (body->inertia) ? 1.0f / body->inertia : 0.0f;
    }


    Type GetType(void) const
    {
        return CIRCLE_SHAPE;
    }
};

struct PolygonShape : public Shape
{
public:
    void Initialize(float density)
    {
        ComputeMass(density);
    }

    void ComputeMass(customFloat density)
    {
        Vec2f centroid(0, 0); 
        customFloat I = 0.0f;
        const customFloat k_inv3 = 1.0f / 3.0f;

        for (uint32 i1 = 0; i1 < m_vertexCount; ++i1)
        {
            Vec2f p1 = m_vertices[i1];
            uint32 i2 = i1 + 1 < m_vertexCount ? i1 + 1 : 0;
            Vec2f p2 = m_vertices[i2];

            customFloat D = Cross(p1, p2);
            customFloat triangleArea = 0.5f * D;

            area += triangleArea;

            centroid +=  (p1 + p2) * triangleArea * k_inv3 ;

            customFloat intx2 = p1.x * p1.x + p2.x * p1.x + p2.x * p2.x;
            customFloat inty2 = p1.y * p1.y + p2.y * p1.y + p2.y * p2.y;
            I += (0.25f * k_inv3 * D) * (intx2 + inty2);
        }
        centroid *= 1.0f / area;
        for (uint32 i = 0; i < m_vertexCount; ++i)
            m_vertices[i] -= centroid;

        body->mass = density * area;
        body->inv_mass = (body->mass) ? 1.0f / body->mass : 0.0f;
        body->inertia = I * density;
        body->inv_inertia = body->inertia ? 1.0f / body->inertia : 0.0f;
    }

    Type GetType(void) const
    {
        return POLYGON_SHAPE;
    }

    void SetBox(customFloat hw, customFloat hh)
    {
        m_vertexCount = 4;
        m_vertices[0].Set(-hw, -hh);
        m_vertices[1].Set(hw, -hh);
        m_vertices[2].Set(hw, hh);
        m_vertices[3].Set(-hw, hh);
        m_normals[0].Set(0.0f, -1.0f);
        m_normals[1].Set(1.0f, 0.0f);
        m_normals[2].Set(0.0f, 1.0f);
        m_normals[3].Set(-1.0f, 0.0f);
    }

    void Set(Vec2f* vertices, uint count)
    {
        assert(count > 2 && count <= MaxPolyVertexCount);
        count = std::min((int)count, MaxPolyVertexCount);

        int rightMost = 0;
        customFloat highestXCoord = vertices[0].x;
        for (uint32 i = 1; i < count; ++i)
        {
            customFloat x = vertices[i].x;
            if (x > highestXCoord)
            {
                highestXCoord = x;
                rightMost = i;
            }
            else if (x == highestXCoord)
                if (vertices[i].y < vertices[rightMost].y)
                    rightMost = i;
        }

        int hull[MaxPolyVertexCount];
        int outCount = 0;
        int indexHull = rightMost;

        for (;;)
        {
            hull[outCount] = indexHull;

            int nextHullIndex = 0;
            for (int i = 1; i < (int)count; ++i)
            {
                if (nextHullIndex == indexHull)
                {
                    nextHullIndex = i;
                    continue;
                }
                Vec2f e1 = vertices[nextHullIndex] - vertices[hull[outCount]];
                Vec2f e2 = vertices[i] - vertices[hull[outCount]];
                customFloat c = Cross(e1, e2);
                if (c < 0.0f)
                    nextHullIndex = i;
                if (c == 0.0f && e2.Length() > e1.Length())
                    nextHullIndex = i;
            }

            ++outCount;
            indexHull = nextHullIndex;
            if (nextHullIndex == rightMost)
            {
                m_vertexCount = outCount;
                break;
            }
        }
        for (uint32 i = 0; i < m_vertexCount; ++i)
            m_vertices[i] = vertices[hull[i]];

        for (uint32 i1 = 0; i1 < m_vertexCount; ++i1)
        {
            uint32 i2 = i1 + 1 < m_vertexCount ? i1 + 1 : 0;
            Vec2f face = m_vertices[i2] - m_vertices[i1];
            assert((face.Length() > EPSILON * EPSILON));
            m_normals[i1] = Vec2f(face.y, -face.x);
            m_normals[i1].Normalize();
        }
    }

    uint32 m_vertexCount;
    Vec2f m_vertices[MaxPolyVertexCount];
    Vec2f m_normals[MaxPolyVertexCount];
};

#endif // SHAPE_H