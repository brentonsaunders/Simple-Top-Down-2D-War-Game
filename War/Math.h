#pragma once

class Math {
public:
	static const double PI;

	static double toDegrees(double);
	static double toRadians(double);
	static double angleDiff(double, double);
	static double euclidean(double, double, double, double);
};