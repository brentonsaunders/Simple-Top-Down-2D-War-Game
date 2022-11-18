#pragma once

#include <vector>
#include "Unit.h"
#include "Soldier.h"
#include "Tank.h"
#include "Fighter.h"
#include "UnitCollection.h"

class Units {
public:
	Units();
	~Units();
	void init(ObstacleMap*);
	void update(DWORD);
	void draw(Canvas*, GameAssets*);
	Unit* addSoldier(Unit::Team, int, int);
	Unit* addTank(Unit::Team, int, int);
	Unit* addFighter(Unit::Team, int, int);
	UnitCollection getUnits();

private:
	std::vector<Unit*> units;
};

