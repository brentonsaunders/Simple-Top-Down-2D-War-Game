#include <Windows.h>
#include "BulletEmitter.h"

using namespace std;

BulletEmitter::BulletEmitter(DWORD timeBetweenShots) {
	this->timeBetweenShots = timeBetweenShots;
}

BulletEmitter::~BulletEmitter() {

}

void BulletEmitter::update(DWORD time) {
	vector<Bullet>::iterator it = bullets.begin();

	if (timeUntilCanShoot > 0) {
		timeUntilCanShoot -= time;
	}

	while (it != bullets.end()) {
		Bullet* bullet = &(*it);

		if (bullet->wasJustFired) {
			bullet->wasJustFired = false;

			timeUntilCanShoot = timeBetweenShots;
		}

		bullet->distanceTraveled += bullet->speed * time;

		if (bullet->distanceTraveled >= bullet->dir.magnitude()) {
			it = bullets.erase(it);

			continue;
		}

		bullet->pos = bullet->start + bullet->dir.unit() * bullet->distanceTraveled;

		++it;
	}
}

void BulletEmitter::draw(Canvas* canvas) {
	canvas->save();

	int size = (int)bullets.size();

	for (int i = 0; i < size; ++i) {
		canvas->line(
			(int)bullets[i].pos.x - 1,
			(int)bullets[i].pos.y - 1,
			(int)bullets[i].pos.x + 1,
			(int)bullets[i].pos.y + 1
		);
	}

	canvas->restore();
}

void BulletEmitter::shoot(Vector2 start, Vector2 end, double speed) {
	if (timeUntilCanShoot > 0) {
		return;
	}

	Bullet bullet;

	bullet.pos = start;
	bullet.start = start;
	bullet.dir = end - start;
	bullet.speed = speed;
	bullet.distanceTraveled = 0;
	bullet.wasJustFired = true;

	bullets.push_back(bullet);
}