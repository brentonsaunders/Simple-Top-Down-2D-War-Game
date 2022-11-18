#include <cmath>
#include "Math.h"

const double Math::PI = 3.14159265358979323;

static double mod(double, double);

double Math::toDegrees(double radians) {
	return radians * 180.0 / PI;
}

double Math::toRadians(double degrees) {
	return degrees * PI / 180.0;
}

double Math::angleDiff(double a, double b) {
	double diff = b - a;

	return mod((diff + Math::PI), 2 * Math::PI) - Math::PI;
}

double Math::euclidean(double x1, double y1, double x2, double y2) {
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

double mod(double a, double n) {
	return a - floor(a / n) * n;
}
