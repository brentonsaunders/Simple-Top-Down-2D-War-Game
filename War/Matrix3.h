#pragma once

#include <string>
#include <vector>
#include "Vector2.h"

class Matrix3 {
public:
	static const Matrix3 ZERO;
	static const Matrix3 IDENTITY;

	Matrix3();
	Matrix3(const Matrix3&);
	Matrix3(double, double, double, double, double, double, double, double, double);
	~Matrix3();
	bool operator==(const Matrix3&) const;
	Matrix3 operator*(const Matrix3&) const;
	Matrix3 operator*(double) const;
	Matrix3 operator/(double) const;
	Matrix3 translate(double, double) const;
	Matrix3 rotate(double) const;
	Matrix3 scale(double, double) const;
	Matrix3 shear(double, double) const;
	double determinant() const;
	Matrix3 transpose() const;
	Matrix3 cofactor() const;
	double cofactor(int, int) const;
	Matrix3 adjoint() const;
	Matrix3 inverse() const;
	std::string toString() const;
	Vector2 apply(const Vector2&) const;
	std::vector<Vector2> apply(std::vector<Vector2>) const;

private:
	double M[3][3];
};
