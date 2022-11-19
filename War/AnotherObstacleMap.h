#pragma once

#include "TileMap.h"

class AnotherObstacleMap {
public:
	AnotherObstacleMap(int, int);
	~AnotherObstacleMap();
	int getWidth() const;
	int getHeight() const;

private:
	TileMap<int> map;
};
