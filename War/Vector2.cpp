#include <sstream>
#include <math.h>
#include "Vector2.h"
#include "Random.h"
#include "Math.h"

using namespace std;

const Vector2 Vector2::ZERO(0, 0);

Vector2::Vector2() {
	x = 0;
	y = 0;
}

Vector2::Vector2(double x, double y) {
	this->x = x;
	this->y = y;
}

Vector2::Vector2(const Vector2& other) {
	x = other.x;
	y = other.y;
}

Vector2::~Vector2() {

}

bool Vector2::operator==(const Vector2& other) const {
	return x == other.x && y == other.y;
}

Vector2 Vector2::operator+(const Vector2& other) const {
	return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const {
	return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator*(double scalar) const {
	return Vector2(scalar * x, scalar * y);
}

Vector2 Vector2::operator/(double scalar) const {
	return Vector2(x / scalar, y / scalar);
}

string Vector2::toString() const {
	stringstream ss;

	ss << x << "," << y;

	return ss.str();
}

Vector2 Vector2::unit() const {
	double mag = magnitude();

	return Vector2(x / mag, y / mag);
}

double Vector2::magnitude() const {
	return sqrt(x * x + y * y);
}

double Vector2::angle() const {
	return atan2(y, x);
}

Vector2 Vector2::rotate(double a) const {
	return fromAngle(angle() + a) * magnitude();
}

Vector2 Vector2::fromAngle(double a) {
	return Vector2(cos(a), sin(a));
}

Vector2 Vector2::random() {
	Random r;

	double a = r.nextDouble() * 2 * Math::PI;

	return fromAngle(a);
}

double Vector2::dot(const Vector2& a, const Vector2& b) {
	return a.x * b.x + a.y * b.y;
}

double Vector2::distance(const Vector2& other) const {
	return (other - *this).magnitude();
}
