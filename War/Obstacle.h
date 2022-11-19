#pragma once

#include "Vector2.h"
#include "GameAssets.h"
#include "Canvas.h"

class Obstacle {
public:
	enum Type {
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

	Obstacle(Type, Vector2);
	~Obstacle();
	void update(DWORD);
	void draw(Canvas*, GameAssets*);
	bool isAlive();
	Vector2 getPos() const;

private:
	Vector2 pos;
	int timeLeft;
	Type type;
};