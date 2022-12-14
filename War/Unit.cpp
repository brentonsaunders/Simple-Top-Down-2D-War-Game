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

void Unit::update(DWORD time, Units *units) {
	if (!isAlive()) {
		deadTime += time;
	}

	if(!path.atEnd()) {
		Vector2 destination = path.nextNode(pos, getTurnRadius());

		steer(time, destination);

		Vector2 ahead = pos + Vector2::fromAngle(angle) * getRadius();

		ObstacleMap* obstacleMap = units->getObstacleMap();

		int aheadX = (int)(ahead.x / 20);
		int aheadY = (int)(ahead.y / 20);
		bool canGoForward = true;

		if (obstacleMap->inBounds(aheadX, aheadY)) {
			ObstacleMap::Type type = obstacleMap->get(aheadX, aheadY);

			if (getCostToTraverse(type) < 0) {
				canGoForward = false;
			}
		}

		if (canGoForward) {
			double distance = getSpeed() * time;

			pos = pos + Vector2::fromAngle(angle) * distance;
		}
	}
	else {
		onArrived();
	}
}

void Unit::steer(DWORD time, const Vector2& destination) {
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

double Unit::getTurnRadius() {
	double turnSpeed = getTurnSpeed();
	double timeToCompleteTurn = (2 * Math::PI) / turnSpeed;
	double C = getSpeed() * timeToCompleteTurn;
	double r = C / (2 * Math::PI);

	return r;
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

int Unit::getCostToTraverse(ObstacleMap::Type type) const {
	if (isAirUnit()) {
		return 0;
	}

	return 0;
}

TileMap<int> Unit::getTraversalMap(const ObstacleMap& map) const {
	int width = map.getWidth();
	int height = map.getHeight();
	TileMap<int> traversalMap(width, height);

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			ObstacleMap::Type type = map.get(x, y);

			traversalMap.set(x, y, getCostToTraverse(type));
		}
	}

	return traversalMap;
}

void Unit::follow(const Path& path) {
	this->path = path;
}

bool Unit::isGroundUnit() const {
	return false;
}

bool Unit::isAirUnit() const {
	return false;
}