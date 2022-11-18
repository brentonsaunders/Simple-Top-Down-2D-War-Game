#pragma once

#include <string>

class Vector2 {
public:
	static const Vector2 ZERO;

	double x, y;

	Vector2();
	Vector2(double, double);
	Vector2(const Vector2&);
	~Vector2();
	bool operator==(const Vector2&) const;
	Vector2 operator+(const Vector2&) const;
	Vector2 operator-(const Vector2&) const;
	Vector2 operator*(double) const;
	Vector2 operator/(double) const;
	Vector2 unit() const;
	double magnitude() const;
	double angle() const;
	Vector2 rotate(double) const;
	std::string toString() const;
	double distance(const Vector2&) const;
	static Vector2 fromAngle(double);
	static Vector2 random();
	static double dot(const Vector2&, const Vector2&);
};
