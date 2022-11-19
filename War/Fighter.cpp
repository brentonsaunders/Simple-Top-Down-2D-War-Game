#include <Windows.h>
#include <iostream>
#include "Fighter.h"
#include "Math.h"
#include "Units.h"
#include "Random.h"

using namespace std;

Fighter::Fighter(Team team) : Unit(team) {
}

Fighter::~Fighter() {

}

void Fighter::init() {
	Unit::init();

	Vector2 destination = path.nextNode(pos, getTurnRadius());

	angle = (destination - pos).angle();
}

void Fighter::update(DWORD time, Units* units) {
	Unit::update(time, units);
}

void Fighter::draw(Canvas* canvas, GameAssets* assets) {
	canvas->save();

	canvas->translate(pos.x, pos.y);

	canvas->rotate(angle);

	canvas->drawBitmap(assets->fighter, -27, -31);

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

void Fighter::onArrived() {
	if (patrolMidpoint == Vector2::ZERO) {
		patrolMidpoint = pos;
	}

	patrol();
}

void Fighter::patrol() {
	Vector2 patrolRadius = patrolMidpoint - pos;

	if (patrolRadius.magnitude() == 0) {
		patrolRadius = Vector2::fromAngle(angle) * 100;
	}

	follow(Path(patrolMidpoint + patrolRadius.rotate(Math::toRadians(45))));
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

bool Fighter::isAirUnit() const { return true; }