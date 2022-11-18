#include <Windows.h>
#include <iostream>
#include "Fighter.h"
#include "Math.h"
#include "Units.h"

using namespace std;

Fighter::Fighter(Team team) : Unit(team) {
	onGuard = false;
}

Fighter::~Fighter() {

}

void Fighter::update(DWORD time, Units* units) {
	Unit::update(time, units);
}

void Fighter::draw(Canvas* canvas, GameAssets* assets) {
	canvas->save();

	canvas->translate(pos.x, pos.y);

	canvas->rotate(angle);

	canvas->drawBitmap(assets->fighter, -27, -31);

	if (onGuard) {
		canvas->fillColor = RGB(255, 0, 0);

		canvas->fillRect((int)guardingPos.x - 3, (int)guardingPos.y - 3,
			6, 6);
	}

	canvas->fillColor = RGB(0, 0, 255);

	canvas->fillRect((int)destination.x - 3, (int)destination.y - 3,
		6, 6);

	canvas->restore();
}

double Fighter::getSpeed() {
	return 800.0 / 5000.0;
}

double Fighter::getTurnSpeed() {
	return Math::toRadians(360.0 / 5000.0);
}

int Fighter::getSteeringAccurary() {
	if (onGuard) {
		return 50;
	}

	return Unit::getSteeringAccurary();
}

void Fighter::onArrived() {
	if (!onGuard) {
		onGuard = true;
		
		guardingPos = pos;

		destination = guardingPos + Vector2::random() * 200;

		return;
	}

	Vector2 diff = pos - guardingPos;
	
	diff = diff.rotate(Math::toRadians(90));

	destination = guardingPos + diff;
}

int Fighter::getTotalHp() const {
	return 20;
}

Unit::Type Fighter::getType() const {
	return FIGHTER;
}

int Fighter::getRadius() const {
	return 1;
}
