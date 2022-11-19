#include <Windows.h>
#include <iostream>
#include "Fighter.h"
#include "Math.h"
#include "Units.h"
#include "Random.h"

using namespace std;

Fighter::Fighter(Team team)
	: Unit(team), bulletEmitter(100) {
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

	bulletEmitter.update(time);

	Unit* opponent = units->getUnits()
		.thatAreAlive()
		.thatAreNear(pos, 300)
		.notFromTeam(getTeam())
		.first();

	if (opponent && isFacingOpponent(opponent)) {
		opponent->damage(12.0 / 2000.0 * time);

		bulletEmitter.shoot(pos, opponent->getPos());
	}
}

bool Fighter::isFacingOpponent(Unit* opponent) {
	double distance = pos.distance(opponent->getPos());

	Vector2 project = pos + Vector2::fromAngle(angle) * distance;

	return opponent->getPos().distance(project) <= opponent->getRadius();
}

void Fighter::draw(Canvas* canvas, GameAssets* assets) {
	Unit::draw(canvas, assets);

	canvas->save();

	bulletEmitter.draw(canvas);

	canvas->translate(pos.x, pos.y);

	canvas->rotate(angle);

	canvas->drawBitmap(assets->fighter, -27, -31);

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
	return 5;
}

Unit::Type Fighter::getType() const {
	return FIGHTER;
}

int Fighter::getRadius() const {
	return 35;
}

bool Fighter::isAirUnit() const { return true; }