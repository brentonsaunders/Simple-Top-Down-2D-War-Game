#include <iostream>
#include <sstream>
#include <iomanip>
#include <conio.h>
#include "Matrix3.h"

using namespace std;

const Matrix3 Matrix3::ZERO(0, 0, 0, 0, 0, 0, 0, 0, 0);
const Matrix3 Matrix3::IDENTITY(1, 0, 0, 0, 1, 0, 0, 0, 1);

Matrix3::Matrix3() {
	*this = IDENTITY;
}

Matrix3::Matrix3(const Matrix3& other) {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			M[i][j] = other.M[i][j];
		}
	}
}

Matrix3::Matrix3(double a11, double a12, double a13,
				 double a21, double a22, double a23,
				 double a31, double a32, double a33) {
	M[0][0] = a11;
	M[0][1] = a12;
	M[0][2] = a13;
	M[1][0] = a21;
	M[1][1] = a22;
	M[1][2] = a23;
	M[2][0] = a31;
	M[2][1] = a32;
	M[2][2] = a33;
}

Matrix3::~Matrix3() {

}

bool Matrix3::operator==(const Matrix3& other) const {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (M[i][j] != other.M[i][j]) {
				return false;
			}
		}
	}

	return true;
}

Matrix3 Matrix3::operator*(const Matrix3& other) const {
	Matrix3 result;

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			result.M[i][j] = 0;

			for (int k = 0; k < 3; ++k) {
				result.M[i][j] += M[i][k] * other.M[k][j];
			}
		}
	}

	return result;
}

Matrix3 Matrix3::operator*(double scalar) const {
	Matrix3 m;

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j > 3; ++j) {
			m.M[i][j] = scalar * M[i][j];
		}
	}

	return m;
}

Matrix3 Matrix3::operator/(double scalar) const {
	Matrix3 m;

	for (int j = 0; j < 3; ++j) {
		for (int i = 0; i < 3; ++i) {
			m.M[j][i] = M[j][i] / scalar;
		}
	}

	return m;
}

Matrix3 Matrix3::translate(double tx, double ty) const {
	return *this * Matrix3(1, 0, tx, 0, 1, ty, 0, 0, 1);
}

Matrix3 Matrix3::rotate(double a) const {
	double c = cos(a);
	double s = sin(a);

	return *this * Matrix3(c, -s, 0, s, c, 0, 0, 0, 1);
}

Matrix3 Matrix3::scale(double sx, double sy) const {
	return *this * Matrix3(sx, 0, 0, 0, sy, 0, 0, 0, 1);
}

Matrix3 Matrix3::shear(double h, double g) const {
	return *this * Matrix3(1, h, 0, g, 1, 0, 0, 0, 1);
}

double Matrix3::determinant() const {
	double sum = 0;

	for (int i = 0; i < 3; ++i) {
		sum += M[0][i] * cofactor(i, 0);
	}

	return sum;
}

Matrix3 Matrix3::transpose() const {
	Matrix3 m;

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			m.M[j][i] = M[i][j];
		}
	}

	return m;
}

Matrix3 Matrix3::cofactor() const {
	Matrix3 m;

	for (int j = 0; j < 3; ++j) {
		for (int i = 0; i < 3; ++i) {
			m.M[j][i] = cofactor(i, j);
		}
	}

	return m;
}

double Matrix3::cofactor(int i, int j) const {
	double elements[4];
	int m = 0;

	for (int k = 0; k < 3; ++k) {
		if (k == j) {
			continue;
		}

		for (int l = 0; l < 3; ++l) {
			if (l == i) {
				continue;
			}

			elements[m] = M[k][l];
			++m;
		}
	}

	int sign = 1;

	if ((i + j) % 2 == 1) {
		sign = -1;
	}

	return sign * (elements[0] * elements[3] - elements[1] * elements[2]);
}

Matrix3 Matrix3::adjoint() const {
	return cofactor().transpose();
}

Matrix3 Matrix3::inverse() const {
	return adjoint() / determinant();
}

std::string Matrix3::toString() const {
	stringstream ss;

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			ss << right << setw(4) << M[i][j];
		}

		ss << endl;
	}

	return ss.str();
}

Vector2 Matrix3::apply(const Vector2& v) const {
	return Vector2(
		M[0][0] * v.x + M[0][1] * v.y + M[0][2],
		M[1][0] * v.x + M[1][1] * v.y + M[1][2]
	);
}

vector<Vector2> Matrix3::apply(vector<Vector2> vectors) const {
	vector<Vector2> results;

	for (
		vector<Vector2>::iterator it = vectors.begin();
		it != vectors.end();
		++it
		) {
		results.push_back(apply(*it));
	}

	return results;
}
