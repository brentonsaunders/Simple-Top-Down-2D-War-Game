#include <Windows.h>
#include <iostream>
#include "Unit.h"
#include "Math.h"
#include "Units.h"

using namespace std;

Random Unit::random;

Unit::Unit(Team team) {
	this->team = team;

	angle = random.nextDouble() * 2 * Math::PI;

	hp = 0;

	deadTime = 0;
}

Unit::~Unit() {

}

void Unit::init() {
	hp = getTotalHp();
}

void Unit::setTeam(Team team) {
	this->team = team;
}

Unit::Team Unit::getTeam() const {
	return team;
}

void Unit::setPos(Vector2 pos) {
	this->pos = pos;
}

Vector2 Unit::getPos() const {
	return pos;
}

void Unit::setDestination(Vector2 destination) {
	this->destination = destination;
}

Vector2 Unit::getDestination() const {
	return destination;
}

void Unit::update(DWORD time, Units *units) {
	if (!isAlive()) {
		deadTime += time;
	}
	/*
	if (pos.distance(destination) > getSteeringAccurary()) {
		steer(time);

		double distance = getSpeed() * time;

		pos = pos + Vector2::fromAngle(angle) * distance;

		if (pos.distance(destination) <= getSteeringAccurary()) {
			onArrived();
		}
	}
	*/
}

void Unit::steer(DWORD time) {
	double targetAngle = (destination - pos).angle();

	double diff = Math::angleDiff(angle, targetAngle);
	int sign = (diff >= 0) ? 1 : -1;

	double deltaAngle = getTurnSpeed() * time;

	if (fabs(deltaAngle) > fabs(diff)) {
		deltaAngle = fabs(diff);
	}

	deltaAngle *= sign;

	angle += deltaAngle;
}

int Unit::getSteeringAccurary() {
	return 5;
}

bool Unit::isAlive() {
	return hp > 0;
}

bool Unit::isDeadForLongEnough() {
	return !isAlive() && deadTime >= 10000;
}

double Unit::getHp() {
	return hp;
}

void Unit::damage(double amount) {
	hp -= amount;

	if (hp < 0) {
		hp = 0;
	}
}

void Unit::draw(Canvas* canvas, GameAssets* assets) {
	canvas->save();

	/*
	int radius = getRadius();

	canvas->ellipse(
		(int)pos.x - radius,
		(int)pos.y - radius,
		2 * radius,
		2 * radius
	);
	*/

	canvas->restore();
}

void Unit::drawFlag(Canvas*canvas, GameAssets*assets) {
	canvas->save();

	Bitmap* flagBitmap = NULL;

	if (team == USA) {
		flagBitmap = assets->usaFlag;
	}
	else if (team == GERMANY) {
		flagBitmap = assets->germanFlag;
	}

	canvas->drawBitmap(flagBitmap, (int)pos.x - 20, (int)pos.y - 20);

	canvas->restore();
}

void Unit::drawHealthBar(Canvas* canvas, GameAssets* assets) {
	const int HEALTH_BAR_WIDTH = 30;
	const int HEALTH_BAR_HEIGHT = 4;

	canvas->save();

	canvas->fillColor = RGB(255, 0, 0);

	canvas->rect((int)pos.x, (int)pos.y - 20, HEALTH_BAR_WIDTH,
		HEALTH_BAR_HEIGHT);

	canvas->fillColor = canvas->strokeColor = RGB(0, 255, 0);

	double ratio = hp / (double)getTotalHp();
	int healthBarInnerWidth = (int)(ratio * (HEALTH_BAR_WIDTH - 2));
	int healthBarInnerHeight = HEALTH_BAR_HEIGHT - 2;

	canvas->rect((int)pos.x + 1, (int)pos.y - 20 + 1, healthBarInnerWidth,
		healthBarInnerHeight);

	canvas->restore();
}

int Unit::getCostToTraverse(ObstacleMap::Obstacle obstacle) const {
	return 0;
}

TileMap Unit::getTraversalMap(const ObstacleMap& map) const {
	int width = map.getWidth();
	int height = map.getHeight();
	TileMap traversalMap(width, height);

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			ObstacleMap::Obstacle obstacle = map.getObstacle(x, y);

			traversalMap.set(x, y, getCostToTraverse(obstacle));
		}
	}

	return traversalMap;
}
