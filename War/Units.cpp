#include <Windows.h>
#include "Units.h"

using namespace std;

Units::Units() {

}

Units::~Units() {

}

void Units::init(ObstacleMap* map) {
	addSoldier(Unit::USA, 100, 100);
	addSoldier(Unit::USA, 150, 100);
	addSoldier(Unit::GERMANY, 200, 200);
	addTank(Unit::GERMANY, 180, 130);
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

Unit* Units::addSoldier(Unit::Team team, int x, int y) {
	Unit* unit = new Soldier(team);

	unit->init();

	unit->setPos(Vector2(x, y));

	units.push_back(unit);

	return unit;
}

Unit* Units::addTank(Unit::Team team, int x, int y) {
	Unit* unit = new Tank(team);

	unit->init();

	unit->setPos(Vector2(x, y));
	unit->setDestination(Vector2(x, y));

	units.push_back(unit);

	return unit;
}

Unit* Units::addFighter(Unit::Team team, int x, int y) {
	Unit* unit = new Fighter(team);

	unit->init();

	unit->setPos(Vector2(x, y));
	unit->setDestination(Vector2(x, y));

	units.push_back(unit);

	return unit;
}

UnitCollection Units::getUnits() {
	return UnitCollection(units);
}
