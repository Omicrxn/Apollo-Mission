#ifndef CUSTOM_MATH_H
#define CUSTOM_MATH_H

#include <algorithm>
#include <cmath>
#include <cassert>
#define PI 3.141592741f
#define EPSILON 0.0001f
typedef float customFloat;
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


inline bool Equal(customFloat a, customFloat b)
{
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