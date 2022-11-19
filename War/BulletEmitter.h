#pragma once

#include <vector>
#include "Canvas.h"
#include "Vector2.h"

class BulletEmitter {
public:
	BulletEmitter(DWORD);
	~BulletEmitter();
	void update(DWORD);
	void draw(Canvas*);
	void shoot(Vector2, Vector2, double speed = 800.0 / 1000.0);

private:
	struct Bullet {
		Vector2 pos;
		Vector2 start;
		Vector2 dir;
		double speed;
		double distanceTraveled;
		bool wasJustFired;
	};

	DWORD timeBetweenShots;
	int timeUntilCanShoot;
	std::vector<Bullet> bullets;
};