#pragma once

#include <stack>
#include "Vector2.h"
#include "AStar.h"

class Path {
public:
	Path();
	Path(AStarPath);
	~Path();
	Vector2 nextNode(Vector2);
	bool atEnd();

private:
	std::stack<Vector2> nodes;
};