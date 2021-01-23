#ifndef CUSTOM_MATH_H
#define CUSTOM_MATH_H

#include <algorithm>
#include <cmath>
#include <cassert>


typedef float customFloat;

const customFloat PI = 3.141592741f;
const customFloat EPSILON = 0.0001f;
template <class T>
class Vec2 {
public:
	T x, y;

	Vec2() :x(0), y(0) {}
	Vec2(T x, T y) : x(x), y(y) {}
	Vec2(const Vec2& v) : x(v.x), y(v.y) {}

	void Set(T x, T y) {
		this->x = x;
		this->y = y;
	}

	Vec2 Zero() {
		return Vec2();
	}

	void Rotate(double deg) {
		double theta = deg / 180.0 * M_PI;
		double cos = cos(theta);
		double sin = sin(theta);
		double tempx = x * cos - y * sin;
		double tempy = x * sin + y * cos;
		x = tx;
		y = ty;
	}

	Vec2& Normalize() {
		if (Length() == 0) return *this;
		*this *= (1.0 / Length());
		return *this;
	}

	float Dist(Vec2 v) const {
		Vec2 d(v.x - x, v.y - y);
		return d.length();
	}
	float Length() const {
		return sqrt(x * x + y * y);
	}
	float LengthSimple() const {
		return x * x + y * y;
	}
	void Truncate(double length) {
		double angle = atan2f(y, x);
		x = length * cos(angle);
		y = length * sin(angle);
	}

	Vec2 Ortho() const {
		return Vec2(y, -x);
	}

	static float Dot(Vec2 v1, Vec2 v2) {
		return v1.x * v2.x + v1.y * v2.y;
	}
	float Dot(Vec2 v)
	{
		return Dot(*this, v);
	}
	static float Cross(Vec2 v1, Vec2 v2) {
		return (v1.x * v2.y) - (v1.y * v2.x);
	}
	float Cross(Vec2 v)
	{
		return Cross(*this, v);
	}

	static Vec2 Pow(Vec2 v)
	{
		return { v.x * v.x,v.y * v.y };
	}
	Vec2& operator=(const Vec2& v) {
		x = v.x;
		y = v.y;
		return *this;
	}

	Vec2 operator+(Vec2& v) {
		return Vec2(x + v.x, y + v.y);
	}
	Vec2 operator-(Vec2& v) {
		return Vec2(x - v.x, y - v.y);
	}

	Vec2 operator*(Vec2& v) {
		return Vec2(x * v.x, y * v.y);
	}

	Vec2& operator+=(Vec2& v) {
		x += v.x;
		y += v.y;
		return *this;
	}
	Vec2& operator-=(Vec2& v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}

	Vec2 operator+(double s) {
		return Vec2(x + s, y + s);
	}
	Vec2 operator-(double s) {
		return Vec2(x - s, y - s);
	}
	Vec2 operator*(double s) {
		return Vec2(x * s, y * s);
	}
	Vec2 operator/(double s) {
		return Vec2(x / s, y / s);
	}


	Vec2& operator+=(double s) {
		x += s;
		y += s;
		return *this;
	}
	Vec2& operator-=(double s) {
		x -= s;
		y -= s;
		return *this;
	}
	Vec2& operator*=(double s) {
		x *= s;
		y *= s;
		return *this;
	}
	Vec2& operator/=(double s) {
		x /= s;
		y /= s;
		return *this;
	}
};

typedef Vec2<int> Vec2i;
typedef Vec2<float> Vec2f;
typedef Vec2<double> Vec2d;
typedef Vec2<customFloat> Vec2c;


struct Matrix2D
{
    union
    {
        struct
        {
            customFloat m00, m01;
            customFloat m10, m11;
        };

        customFloat m[2][2];
        customFloat v[4];
    };

    Matrix2D() {}
    Matrix2D(customFloat radians)
    {
        customFloat c = std::cos(radians);
        customFloat s = std::sin(radians);

        m00 = c; m01 = -s;
        m10 = s; m11 = c;
    }

    Matrix2D(customFloat a, customFloat b, customFloat c, customFloat d)
        : m00(a), m01(b)
        , m10(c), m11(d)
    {
    }

    void Set(customFloat radians)
    {
        customFloat c = std::cos(radians);
        customFloat s = std::sin(radians);

        m00 = c; m01 = -s;
        m10 = s; m11 = c;
    }

    Matrix2D Abs(void) const
    {
        return Matrix2D(std::abs(m00), std::abs(m01), std::abs(m10), std::abs(m11));
    }

    Vec2c AxisX(void) const
    {
        return Vec2c(m00, m10);
    }

	Vec2c AxisY(void) const
    {
        return Vec2c(m01, m11);
    }

    Matrix2D Transpose(void) const
    {
        return Matrix2D(m00, m10, m01, m11);
    }

    const Vec2c operator*(const Vec2c& rhs) const
    {
        return Vec2c(m00 * rhs.x + m01 * rhs.y, m10 * rhs.x + m11 * rhs.y);
    }

    const Matrix2D operator*(const Matrix2D& rhs) const
    {

        return Matrix2D(
            m[0][0] * rhs.m[0][0] + m[0][1] * rhs.m[1][0],
            m[0][0] * rhs.m[0][1] + m[0][1] * rhs.m[1][1],
            m[1][0] * rhs.m[0][0] + m[1][1] * rhs.m[1][0],
            m[1][0] * rhs.m[0][1] + m[1][1] * rhs.m[1][1]
        );
    }
};

inline Vec2c Min(const Vec2c& a, const Vec2c& b)
{
    return Vec2c(std::min(a.x, b.x), std::min(a.y, b.y));
}

inline Vec2c Max(const Vec2c& a, const Vec2c& b)
{
    return Vec2c(std::max(a.x, b.x), std::max(a.y, b.y));
}

inline customFloat Dot(const Vec2c& a, const Vec2c& b)
{
    return a.x * b.x + a.y * b.y;
}

inline customFloat DistSqr( Vec2c& a,  Vec2c& b)
{
	Vec2c c = a - b;
    return Dot(c, c);
}

inline Vec2c Cross(const Vec2c& v, customFloat a)
{
    return Vec2c(a * v.y, -a * v.x);
}

inline Vec2c Cross(customFloat a, const Vec2c& v)
{
    return Vec2c(-a * v.y, a * v.x);
}

inline customFloat Cross(const Vec2c& a, const Vec2c& b)
{
    return a.x * b.y - a.y * b.x;
}

// Comparison with tolerance of EPSILON
inline bool Equal(customFloat a, customFloat b)
{
    // <= instead of < for NaN comparison safety
    return std::abs(a - b) <= EPSILON;
}

inline customFloat Sqr(customFloat a)
{
    return a * a;
}

inline customFloat Clamp(customFloat min, customFloat max, customFloat a)
{
    if (a < min) return min;
    if (a > max) return max;
    return a;
}

inline int Round(customFloat a)
{
    return (int)(a + 0.5f);
}

inline customFloat Random(customFloat l, customFloat h)
{
    customFloat a = (customFloat)rand();
    a /= RAND_MAX;
    a = (h - l) * a + l;
    return a;
}

inline bool BiasGreaterThan(customFloat a, customFloat b)
{
    const customFloat k_biasRelative = 0.95f;
    const customFloat k_biasAbsolute = 0.01f;
    return a >= b * k_biasRelative + a * k_biasAbsolute;
}

#endif // CUSTOM_MATH_H