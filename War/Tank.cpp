#include <Windows.h>
#include "Tank.h"
#include "Math.h"
#include "Tank.h"
#include "Units.h"

Tank::Tank(Team team) : Unit(team), bulletEmitter(100) {
	turretAngle = random.nextDouble() * 2 * Math::PI;
}

Tank::~Tank() {

}

void Tank::update(DWORD time, Units *units) {
	Unit::update(time, units);

	bulletEmitter.update(time);

	doRollOverDamage(time, units);

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
			opponent->damage(20.0 / 2000.0 * time);

			bulletEmitter.shoot(pos, opponent->getPos(), 800.0 / 5000.0);
		}
	}
}

void Tank::doRollOverDamage(DWORD time, Units* units) {
	units->getUnits()
		.except(this)
		.thatAreAlive()
		.thatAreNear(pos, 20)
		.thatAreGroundUnits()
		.damage(5.0 / 1000.0 * time);
}


void Tank::turnToFaceOpponent(DWORD time, Unit *opponent) {
	Vector2 dir = opponent->getPos() - pos;

	double angleDiff = Math::angleDiff(turretAngle, dir.angle());

	double theta = 0;

	if (angleDiff < 0) {
		theta = Math::toRadians(-360.0 / 10000.0 * time);

		if (theta < angleDiff) {
			theta = angleDiff;
		}
	}
	else if (angle > 0) {
		theta = Math::toRadians(360.0 / 10000.0 * time);

		if (theta > angleDiff) {
			theta = angleDiff;
		}
	}

	turretAngle += theta;
}

bool Tank::isFacingOpponent(Unit *opponent) {
	double distance = pos.distance(opponent->getPos());

	Vector2 project = pos + Vector2::fromAngle(turretAngle) * distance;

	return opponent->getPos().distance(project) <= opponent->getRadius();
}

void Tank::draw(Canvas* canvas, GameAssets* assets) {
	canvas->save();

	canvas->translate(pos.x, pos.y);

	canvas->rotate(angle);

	canvas->drawBitmap(assets->tank, -20, -13, 39, 26, 1, 0, 39, 26);

	canvas->restore();

	canvas->save();

	canvas->translate(pos.x, pos.y);

	canvas->rotate(turretAngle);

	canvas->drawBitmap(assets->tank, -14, -11, 60, 20, 0, 26, 60, 20);

	bulletEmitter.draw(canvas);

	canvas->restore();
}

double Tank::getSpeed() {
	return 800.0 / 40000.0;
}

double Tank::getTurnSpeed() {
	return Math::toRadians(360.0 / 5000.0);
}

void Tank::onArrived() {

}

int Tank::getTotalHp() const {
	return 100;
}

Unit::Type Tank::getType() const {
	return TANK;
}

int Tank::getRadius() const {
	return 1;
}

bool Tank::isGroundUnit() const { return true; }
