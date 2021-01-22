#ifndef __VEC2_H__
#define __VEC2_H__

#include <math.h>
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
		if (length() == 0) return *this;
		*this *= (1.0 / length());
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


#endif