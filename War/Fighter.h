#pragma once

#include "Unit.h"
#include "Canvas.h"
#include "GameAssets.h"

class Fighter : public Unit {
public:
	Fighter(Team);
	~Fighter();
	void init();
	void update(DWORD, Units*);
	void draw(Canvas*, GameAssets*);
	double getSpeed();
	double getTurnSpeed();
	void onArrived();
	int getTotalHp() const;
	Type getType() const;
	int getRadius() const;
	bool isAirUnit() const;

private:
	Vector2 patrolMidpoint;

	void patrol();
};
