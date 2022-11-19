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
	addUnit(Unit::SOLDIER, Unit::USA, 40, 40, 700,500);
	addUnit(Unit::SOLDIER, Unit::USA, 300, 300, 150, 100);
	addUnit(Unit::SOLDIER, Unit::GERMANY, 700, 400, 200, 200);
	addUnit(Unit::TANK, Unit::GERMANY, 300, 500, 180, 130);
	addUnit(Unit::FIGHTER, Unit::GERMANY, 0, 0, 500, 500);
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

Unit* Units::addUnit(
	Unit::Type type,
	Unit::Team team,
	int startX,
	int startY,
	int endX,
	int endY
) {
	Unit* unit;

	switch (type) {
	case Unit::SOLDIER:
		unit = new Soldier(team);
		break;
	case Unit::TANK:
		unit = new Tank(team);
		break;
	case Unit::FIGHTER:
		unit = new Fighter(team);
		break;
	default:
		return NULL;
	}

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

	unit->follow(Path(path));

	unit->init();

	units.push_back(unit);

	return unit;
}

UnitCollection Units::getUnits() {
	return UnitCollection(units);
}
