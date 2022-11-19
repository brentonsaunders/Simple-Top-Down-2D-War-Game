#pragma once

#include <vector>
#include "Unit.h"
#include "Soldier.h"
#include "Tank.h"
#include "Fighter.h"
#include "UnitCollection.h"

class Units {
public:
	Units(ObstacleMap*);
	~Units();
	void init();
	void update(DWORD);
	void draw(Canvas*, GameAssets*);
	Unit* addUnit(Unit::Type, Unit::Team, int, int, int, int);
	bool addObstacle(ObstacleMap::Type, int, int);
	ObstacleMap* getObstacleMap() const;
	UnitCollection getUnits();

private:
	std::vector<Unit*> units;
	ObstacleMap* obstacleMap;
};

