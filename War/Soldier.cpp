#include <Windows.h>
#include <set>
#include <iostream>
#include "Soldier.h"
#include "Math.h"
#include "Soldier.h"
#include "Units.h"

using namespace std;

Soldier::Soldier(Team team) : Unit(team), bulletEmitter(100) {}

Soldier::~Soldier() {

}

void Soldier::update(DWORD time, Units* units) {
	Unit::update(time, units);

	bulletEmitter.update(time);

	std::vector<Type> attackable;

	attackable.push_back(SOLDIER);

	Unit* opponent = units->getUnits()
		.thatAreAlive()
		.thatAreNear(pos, 200)
		.notFromTeam(getTeam())
		.ofTypes(attackable)
		.sortedByTypeAndHp(attackable)
		.first();

	if (opponent) {
		turnToFaceOpponent(time, opponent);

		if (isFacingOpponent(opponent)) {
			opponent->damage(5.0 / 2000.0 * time);

			bulletEmitter.shoot(pos, opponent->getPos());
		}
	}
}

void Soldier::turnToFaceOpponent(DWORD time, Unit* opponent) {
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

bool Soldier::isFacingOpponent(Unit* opponent) {
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
	return Math::toRadians(360.0 / 1000.0);
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

int Soldier::getCostToTraverse(ObstacleMap::Type type) const {
	switch (type) {
	case ObstacleMap::TREES:
	case ObstacleMap::WATER:
	case ObstacleMap::HEDGEHOG:
		return -1;
	case ObstacleMap::GROUND1:
		return 1;
	case ObstacleMap::GROUND2:
		return 2;
	case ObstacleMap::GROUND3:
		return 3;
	case ObstacleMap::GROUND4:
		return 4;
	case ObstacleMap::GROUND5:
		return 5;
	}

	return 0;
}

bool Soldier::isGroundUnit() const { return true; }