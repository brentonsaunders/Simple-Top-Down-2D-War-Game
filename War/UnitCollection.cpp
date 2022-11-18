#include <Windows.h>
#include <algorithm>
#include "UnitCollection.h"

using namespace std;

UnitCollection::UnitCollection(const vector<Unit*> &units) {
	this->units = units;
}

UnitCollection::~UnitCollection() {

}

UnitCollection UnitCollection::thatAreNear(Vector2 pos, int radius) const {
	int size = (int)units.size();
	vector<Unit*> result;

	for (int i = 0; i < size; ++i) {
		if (units[i]->getPos().distance(pos) < radius) {
			result.push_back(units[i]);
		}
	}

	return UnitCollection(result);
}

UnitCollection UnitCollection::thatAreAlive() const {
	int size = (int)units.size();
	vector<Unit*> result;

	for (int i = 0; i < size; ++i) {
		if (units[i]->isAlive()) {
			result.push_back(units[i]);
		}
	}

	return UnitCollection(result);
}

UnitCollection UnitCollection::notFromTeam(Unit::Team team) const {
	int size = (int)units.size();
	vector<Unit*> result;

	for (int i = 0; i < size; ++i) {
		if (units[i]->getTeam() != team) {
			result.push_back(units[i]);
		}
	}

	return UnitCollection(result);
}

UnitCollection UnitCollection::ofTypes(vector<Unit::Type> types) const {
	int size = (int)units.size();
	vector<Unit*> result;

	for (int i = 0; i < size; ++i) {
		if (find(types.begin(), types.end(), units[i]->getType()) != types.end()) {
			result.push_back(units[i]);
		}
	}

	return UnitCollection(result);
}


UnitCollection UnitCollection::sortedByTypeAndHp(vector<Unit::Type> types) const {
	struct Compare {
		Compare(vector<Unit::Type> types) {
			this->types = types;
		}

		bool operator()(Unit* a, Unit* b) {
			vector<Unit::Type>::iterator itA = find(types.begin(), types.end(), a->getType());
			vector<Unit::Type>::iterator itB = find(types.begin(), types.end(), b->getType());

			if (itA == types.end() && itB == types.end()) {
				return false;
			}

			if (itA < itB) {
				return true;
			}
			else if (itA > itB) {
				return false;
			}

			return a->getHp() < b->getHp();
		}

	private:
		vector<Unit::Type> types;
	} compare(types);

	vector<Unit*> results(units);

	sort(results.begin(), results.end(), compare);

	return UnitCollection(results);
}

Unit* UnitCollection::first() const {
	if (units.size() == 0) {
		return NULL;
	}

	return units[0];
}

Unit* UnitCollection::last() const {
	if (units.size() == 0) {
		return NULL;
	}

	return units.back();
}

vector<Unit*> UnitCollection::all() const {
	return units;
}
