#pragma once

#include <stack>
#include <vector>
#include "Vector2.h"
#include "AStar.h"

class Path {
public:
	Path();
	Path(const Path&);
	Path(const std::vector<Vector2>&);
	Path(const Vector2&);
	Path(AStarPath);
	~Path();
	Vector2 nextNode(Vector2, double);
	bool atEnd();

private:
	std::vector<Vector2> nodes;
};