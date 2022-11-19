#pragma once

#include <vector>
#include "Vector2.h"
#include "AStar.h"

class Path {
public:
	Path(AStarPath);
	~Path();

private:
	std::vector<Vector2> nodes;
};