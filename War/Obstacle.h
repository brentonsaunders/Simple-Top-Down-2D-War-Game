#pragma once

#include "Vector2.h"
#include "GameAssets.h"
#include "Canvas.h"

class Obstacle {
public:
	enum Type {
		NONE,
		GROUND0,
		GROUND1,
		GROUND2,
		GROUND3,
		GROUND4,
		GROUND5,
		TRENCH,
		HEDGEHOG,
		WATER,
		TREES,
	};

	Obstacle(Type, int, int);
	~Obstacle();
	void update(DWORD);
	bool isAlive();
	int getX() const;
	int getY() const;

private:
	int x, y;
	int timeLeft;
	Type type;
};
