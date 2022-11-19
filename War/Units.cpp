#include <Windows.h>
#include <iostream>
#include "Units.h"
#include "AStar.h"

using namespace std;

Units::Units(ObstacleMap* obstacleMap) {
	this->obstacleMap = obstacleMap;
}

Units::~Units() {

}

void Units::init() {
	addSoldier(Unit::USA, 40, 40, 700,500);
	// addSoldier(Unit::USA, 300, 300, 150, 100);
	// addSoldier(Unit::GERMANY, 700, 400, 200, 200);
	// addTank(Unit::GERMANY, 300, 500, 180, 130);
}

void Units::update(DWORD time) {
	vector<Unit*>::iterator it = units.begin();

	while (it != units.end()) {
		Unit* unit = *it;

		if (unit->isDeadForLongEnough()) {
			delete unit;

			it = units.erase(it);

			continue;
		}
		else if(unit->isAlive()) {
			unit->update(time, this);
		}

		++it;
	}
}

void Units::draw(Canvas* canvas, GameAssets* assets) {
	int size = (int)units.size();

	for (int i = 0; i < size; ++i) {
		if (units[i]->isAlive()) {
			units[i]->draw(canvas, assets);
		}
	}

	for (int i = 0; i < size; ++i) {
		if (units[i]->isAlive()) {
			units[i]->drawFlag(canvas, assets);
			units[i]->drawHealthBar(canvas, assets);
		}
	}
}

Unit* Units::addSoldier(Unit::Team team, int startX, int startY, int endX, int endY) {
	Unit* unit = new Soldier(team);

	unit->init();

	unit->setPos(Vector2(startX, startY));

	TileMap traversalMap = unit->getTraversalMap(*obstacleMap);

	AStar aStar(unit->getTraversalMap(*obstacleMap));

	if (!aStar.findPath(
		startX / 20,
		startY / 20,
		endX / 20,
		endY / 20
	)) {
		cout << "Couldn't find a path!" << endl;

		delete unit;

		return NULL;
	}

	AStarPath path = aStar.getPath();

	// cout << traversalMap.toString() << endl;

	// cout << aStar.getLatency() << endl;

	// cout << path.toString() << endl;

	unit->follow(Path(path));

	units.push_back(unit);

	return unit;
}

Unit* Units::addTank(Unit::Team team, int startX, int startY, int endX, int endY) {
	Unit* unit = new Tank(team);

	unit->init();

	unit->setPos(Vector2(startX, startY));

	units.push_back(unit);

	return unit;
}

Unit* Units::addFighter(Unit::Team team, int startX, int startY, int endX, int endY) {
	Unit* unit = new Fighter(team);

	unit->init();

	unit->setPos(Vector2(startX, startY));

	units.push_back(unit);

	return unit;
}

UnitCollection Units::getUnits() {
	return UnitCollection(units);
}
