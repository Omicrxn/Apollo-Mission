#ifndef SHAPE_H
#define SHAPE_H

#include "Body.h"

#define MaxPolyVertexCount 64

struct Shape
{
    enum Type
    {
        eCircle,
        ePoly,
        eCount
    };

    Shape() {}
    virtual void Initialize(float density) = 0;
    virtual void ComputeMass(customFloat density) = 0;
    virtual void SetOrient(customFloat radians) = 0;
    virtual Type GetType() const = 0;

    Body* body;
    customFloat area;
    // For circle shape
    customFloat radius;

    // For Polygon shape
    Matrix2D u; // Orientation matrix from model to world
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

    void SetOrient(customFloat radians) {}

    Type GetType(void) const
    {
        return eCircle;
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
        // Calculate centroid and moment of interia
        Vec2f centroid(0, 0); // centroid
        customFloat I = 0.0f;
        const customFloat k_inv3 = 1.0f / 3.0f;

        for (uint32 i1 = 0; i1 < m_vertexCount; ++i1)
        {
            // Triangle vertices, third vertex implied as (0, 0)
            Vec2f p1 = m_vertices[i1];
            uint32 i2 = i1 + 1 < m_vertexCount ? i1 + 1 : 0;
            Vec2f p2 = m_vertices[i2];

            customFloat D = Cross(p1, p2);
            customFloat triangleArea = 0.5f * D;

            area += triangleArea;

            // Use area to weight the centroid average, not just vertex position
            centroid +=  (p1 + p2) * triangleArea * k_inv3 ;

            customFloat intx2 = p1.x * p1.x + p2.x * p1.x + p2.x * p2.x;
            customFloat inty2 = p1.y * p1.y + p2.y * p1.y + p2.y * p2.y;
            I += (0.25f * k_inv3 * D) * (intx2 + inty2);
        }

        centroid *= 1.0f / area;

        // Translate vertices to centroid (make the centroid (0, 0)
        // for the polygon in model space)
        // Not really necessary, but I like doing this anyway
        for (uint32 i = 0; i < m_vertexCount; ++i)
            m_vertices[i] -= centroid;

        body->mass = density * area;
        body->inv_mass = (body->mass) ? 1.0f / body->mass : 0.0f;
        body->inertia = I * density;
        body->inv_inertia = body->inertia ? 1.0f / body->inertia : 0.0f;
    }

    void SetOrient(customFloat radians)
    {
        u.Set(radians);
    }

    Type GetType(void) const
    {
        return ePoly;
    }

    // Half width and half height
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
        // No hulls with less than 3 vertices (ensure actual polygon)
        assert(count > 2 && count <= MaxPolyVertexCount);
        count = std::min((int)count, MaxPolyVertexCount);

        // Find the right most point on the hull
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

            // If matching x then take farthest negative y
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

            // Search for next index that wraps around the hull
            // by computing cross products to find the most counter-clockwise
            // vertex in the set, given the previos hull index
            int nextHullIndex = 0;
            for (int i = 1; i < (int)count; ++i)
            {
                // Skip if same coordinate as we need three unique
                // points in the set to perform a cross product
                if (nextHullIndex == indexHull)
                {
                    nextHullIndex = i;
                    continue;
                }

                // Cross every set of three unique vertices
                // Record each counter clockwise third vertex and add
                // to the output hull
                // See : http://www.oocities.org/pcgpe/math2d.html
                Vec2f e1 = vertices[nextHullIndex] - vertices[hull[outCount]];
                Vec2f e2 = vertices[i] - vertices[hull[outCount]];
                customFloat c = Cross(e1, e2);
                if (c < 0.0f)
                    nextHullIndex = i;

                // Cross product is zero then e vectors are on same line
                // therefor want to record vertex farthest along that line
                if (c == 0.0f && e2.Length() > e1.Length())
                    nextHullIndex = i;
            }

            ++outCount;
            indexHull = nextHullIndex;

            // Conclude algorithm upon wrap-around
            if (nextHullIndex == rightMost)
            {
                m_vertexCount = outCount;
                break;
            }
        }

        // Copy vertices into shape's vertices
        for (uint32 i = 0; i < m_vertexCount; ++i)
            m_vertices[i] = vertices[hull[i]];

        // Compute face normals
        for (uint32 i1 = 0; i1 < m_vertexCount; ++i1)
        {
            uint32 i2 = i1 + 1 < m_vertexCount ? i1 + 1 : 0;
            Vec2f face = m_vertices[i2] - m_vertices[i1];

            // Ensure no zero-length edges, because that's bad
            assert((face.Length() > EPSILON * EPSILON));

            // Calculate normal with 2D cross product between vector and scalar
            m_normals[i1] = Vec2f(face.y, -face.x);
            m_normals[i1].Normalize();
        }
    }

    // The extreme point along a direction within a polygon
    Vec2f GetSupport(const Vec2f& dir)
    {
        customFloat bestProjection = -FLT_MAX;
        Vec2f bestVertex;

        for (uint i = 0; i < m_vertexCount; ++i)
        {
            Vec2f v = m_vertices[i];
            customFloat projection = Dot(v, dir);

            if (projection > bestProjection)
            {
                bestVertex = v;
                bestProjection = projection;
            }
        }

        return bestVertex;
    }

    uint32 m_vertexCount;
    Vec2f m_vertices[MaxPolyVertexCount];
    Vec2f m_normals[MaxPolyVertexCount];
};

#endif // SHAPE_H