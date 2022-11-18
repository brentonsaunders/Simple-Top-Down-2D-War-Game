#include <Windows.h>
#include <set>
#include <iostream>
#include "Soldier.h"
#include "Math.h"
#include "Soldier.h"
#include "Units.h"

using namespace std;

Soldier::Soldier(Team team) : Unit(team), bulletEmitter(100) {
	opponent = NULL;
}

Soldier::~Soldier() {

}

void Soldier::update(DWORD time, Units* units) {
	Unit::update(time, units);

	bulletEmitter.update(time);

	if (!opponent || !opponent->isAlive()) {
		opponent = NULL;

		std::vector<Type> attackable;

		attackable.push_back(SOLDIER);

		Unit* unit = units->getUnits()
			.thatAreAlive()
			.thatAreNear(pos, 200)
			.notFromTeam(getTeam())
			.ofTypes(attackable)
			.sortedByTypeAndHp(attackable)
			.first();

		if (unit) {
			opponent = unit;
		}
	}
	else {
		turnToFaceOpponent(time);

		if (isFacingOpponent()) {
			opponent->damage(5.0 / 2000.0 * time);

			bulletEmitter.shoot(pos, opponent->getPos(), 800.0 / 5000.0);
		}
	}
}

void Soldier::turnToFaceOpponent(DWORD time) {
	Vector2 dir = opponent->getPos() - pos;

	double angleDiff = Math::angleDiff(angle, dir.angle());

	double theta = 0;

	if (angleDiff < 0) {
		theta = Math::toRadians(-360.0 / 2000.0 * time);

		if (theta < angleDiff) {
			theta = angleDiff;
		}
	} else if (angle > 0) {
		theta = Math::toRadians(360.0 / 2000.0 * time);

		if (theta > angleDiff) {
			theta = angleDiff;
		}
	}

	angle += theta;
}

bool Soldier::isFacingOpponent() {
	double distance = pos.distance(opponent->getPos());

	Vector2 project = pos + Vector2::fromAngle(angle) * distance;

	return opponent->getPos().distance(project) <= opponent->getRadius();
}

void Soldier::draw(Canvas* canvas, GameAssets* assets) {
	Unit::draw(canvas, assets);

	canvas->save();

	canvas->translate(pos.x, pos.y);

	canvas->rotate(angle);

	canvas->drawBitmap(assets->soldier, -11, -7);

	bulletEmitter.draw(canvas);

	canvas->restore();
}

double Soldier::getSpeed() {
	return 800.0 / 10000.0;
}

double Soldier::getTurnSpeed() {
	return Math::toRadians(360.0 / 5000.0);
}

void Soldier::onArrived() {

}

int Soldier::getTotalHp() const {
	return 5;
}

Unit::Type Soldier::getType() const {
	return SOLDIER;
}

int Soldier::getRadius() const {
	return 12;
}