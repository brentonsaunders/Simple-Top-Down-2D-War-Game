#pragma once

#include <vector>
#include <set>
#include "Unit.h"
#include "Vector2.h"

class UnitCollection {
public:
	UnitCollection(const std::vector<Unit*>&);
	~UnitCollection();
	UnitCollection thatAreAlive() const;
	UnitCollection thatAreNear(Vector2, int) const;
	UnitCollection notFromTeam(Unit::Team) const;
	UnitCollection ofTypes(std::vector<Unit::Type>) const;
	UnitCollection sortedByTypeAndHp(std::vector<Unit::Type>) const;
	Unit* first() const;
	Unit* last() const;
	std::vector<Unit*> all() const;
private:
	std::vector<Unit*> units;
};
